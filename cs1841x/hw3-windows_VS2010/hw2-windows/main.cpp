//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <stack>
#include <limits>
#include <FreeImage.h>
#include "Transform.h"

using namespace std;

vec3 eyeinit;
vec3 upinit ;
vec3 center ;
int w, h ;
float fovy ;

static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {cube, sphere, teapot, tri} ;
float sx, sy ; // the scale in x and y 
float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10 ; 
float lightposn [4*numLights] ; // Light Positions
float lightcolor[4*numLights] ; // Light Colors
float lightransf[4*numLights] ; // Lights transformed by modelview
int numused ;                     // How many lights are used 

// Materials (read from file) 
// With multiple objects, these are colors for each.
float ambient[4] ; 
float diffuse[4] ; 
float specular[4] ; 
float emission[4] ; 
float shininess ; 

//几何数据
int maxverts;
vector<float*> vertex;

// For multiple objects, read from a file.
int numobjects ; 
struct object {
	shape type ; 
	float size ;
	float ambient[4] ; 
	float diffuse[4] ; 
	float specular[4] ;
	float emission[4] ; 
	float shininess ;
	mat4 transform ;
	int verindex[3];//for tri
};
vector<object*> objects;

void matransform (stack<mat4> &transfstack, float * values)
{
	mat4 transform = transfstack.top(); 
	vec4 valvec = vec4(values[0],values[1],values[2],values[3]); 
	vec4 newval = transform * valvec; 
	for (int i = 0; i < 4; i++) values[i] = newval[i]; 
}

void rightmultiply (const mat4 & M, stack<mat4> &transfstack)
{
	mat4 &T = transfstack.top(); 
	T = T * M;
}

bool readvals (stringstream &s, const int numvals, float * values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i]; 
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n"; 
			return false;
		}
	}
	return true;
}

void readfile (const char * filename)
{
	string str, cmd; 
	ifstream in;
	in.open(filename); 
	if (in.is_open()) {

		// I need to implement a matrix stack to store transforms.  
		// This is done using standard STL Templates 
		stack <mat4> transfstack; 
		transfstack.push(mat4(1.0));  // identity

		getline (in, str); 
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				// Ruled out comment and blank lines 

				stringstream s(str);
				s >> cmd; 
				int i; 
				float values[10]; // Position and color for light, colors for others
				// Up to 10 params for cameras.  
				bool validinput; // Validity of input 

				// Process the light, add it to database.
				// Lighting Command
				if (cmd == "light") {
					if (numused == numLights) { // No more Lights 
						cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
					} else {
						validinput = readvals(s, 8, values); // Position/color for lts.
						if (validinput) {

							// YOUR CODE FOR HW 2 HERE. 
							// Note that values[0...7] shows the read in values 
							// Make use of lightposn[] and lightcolor[] arrays in variables.h
							// Those arrays can then be used in display too. 
							for (i = 0; i < 4; i++) {
								lightposn[4*numused + i] = values[i];
								lightcolor[4*numused + i] = values[i+4];
							}
							++numused; 
						}
					}
				}

				// Material Commands 
				// Ambient, diffuse, specular, shininess properties for each object.
				// Filling this in is pretty straightforward, so I've left it in 
				// the skeleton, also as a hint of how to do the more complex ones.
				// Note that no transforms/stacks are applied to the colors. 

				else if (cmd == "ambient") {
					validinput = readvals(s, 4, values); // colors 
					if (validinput) {
						for (i = 0; i < 4; i++) {
							ambient[i] = values[i]; 
						}
					}
				} else if (cmd == "diffuse") {
					validinput = readvals(s, 4, values); 
					if (validinput) {
						for (i = 0; i < 4; i++) {
							diffuse[i] = values[i]; 
						}
					}
				} else if (cmd == "specular") {
					validinput = readvals(s, 4, values); 
					if (validinput) {
						for (i = 0; i < 4; i++) {
							specular[i] = values[i]; 
						}
					}
				} else if (cmd == "emission") {
					validinput = readvals(s, 4, values); 
					if (validinput) {
						for (i = 0; i < 4; i++) {
							emission[i] = values[i]; 
						}
					}
				} else if (cmd == "shininess") {
					validinput = readvals(s, 1, values); 
					if (validinput) {
						shininess = values[0]; 
					}
				} else if (cmd == "size") {
					validinput = readvals(s,2,values); 
					if (validinput) { 
						w = (int) values[0]; h = (int) values[1]; 
					} 
				} else if (cmd == "camera") {
					validinput = readvals(s,10,values); // 10 values eye cen up fov
					if (validinput) {

						// YOUR CODE FOR HW 2 HERE
						// Use all of values[0...9]
						// You may need to use the upvector fn in Transform.cpp
						// to set up correctly. 
						// Set eyeinit upinit center fovy in variables.h 
						eyeinit[0] = values[0];
						eyeinit[1] = values[1];
						eyeinit[2] = values[2];
						center[0] = values[3];
						center[1] = values[4];
						center[2] = values[5];
						upinit[0] = values[6];
						upinit[1] = values[7];
						upinit[2] = values[8];
						fovy = values[9];
					}
				}

				// I've left the code for loading objects in the skeleton, so 
				// you can get a sense of how this works.  
				// Also look at demo.txt to get a sense of why things are done this way.
				else if (cmd == "sphere" || cmd == "cube" || cmd == "teapot") {
					validinput = readvals(s, 1, values); 
					if (validinput) {
						object * obj = new object; 
						obj->size = values[0];

						// Set the object's light properties
						for (i = 0; i < 4; i++) {
							(obj->ambient)[i] = ambient[i]; 
							(obj->diffuse)[i] = diffuse[i]; 
							(obj->specular)[i] = specular[i]; 
							(obj->emission)[i] = emission[i];
						}
						obj->shininess = shininess; 

						// Set the object's transform
						obj->transform = transfstack.top(); 

						// Set the object's type
						if (cmd == "sphere") {
							obj->type = sphere; 
						} else if (cmd == "cube") {
							obj->type = cube; 
						} else if (cmd == "teapot") {
							obj->type = teapot; 
						}
						objects.push_back(obj);
					}
				}
				else if (cmd == "tri")
				{
					validinput = readvals(s, 3, values); 
					if (validinput) {
						object * obj = new object; 
						obj->verindex[0] = (int)values[0];
						obj->verindex[1] = (int)values[1];
						obj->verindex[2] = (int)values[2];

						// Set the object's light properties
						for (i = 0; i < 4; i++) {
							(obj->ambient)[i] = ambient[i]; 
							(obj->diffuse)[i] = diffuse[i]; 
							(obj->specular)[i] = specular[i]; 
							(obj->emission)[i] = emission[i];
						}
						obj->shininess = shininess; 

						// Set the object's transform
						obj->transform = transfstack.top(); 

						// Set the object's type
						if (cmd == "sphere") {
							obj->type = sphere; 
						} else if (cmd == "cube") {
							obj->type = cube; 
						} else if (cmd == "teapot") {
							obj->type = teapot; 
						}
						objects.push_back(obj);
					}
				}
				else if (cmd == "translate") {
					validinput = readvals(s,3,values); 
					if (validinput) {

						// YOUR CODE FOR HW 2 HERE.  
						// Think about how the transformation stack is affected
						// You might want to use helper functions on top of file. 
						// Also keep in mind what order your matrix is!
						mat4 trans(
							1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							values[0], values[1], values[2], 1.0f
							);
						rightmultiply(trans, transfstack);
					}
				}
				else if (cmd == "scale") {
					validinput = readvals(s,3,values); 
					if (validinput) {

						// YOUR CODE FOR HW 2 HERE.  
						// Think about how the transformation stack is affected
						// You might want to use helper functions on top of file.  
						// Also keep in mind what order your matrix is!
						mat4 scale(
							values[0], 0.0f, 0.0f, 0.0f,
							0.0f, values[1], 0.0f, 0.0f,
							0.0f, 0.0f, values[2], 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f
							);
						rightmultiply(scale, transfstack);
					}
				}
				else if (cmd == "rotate") {
					validinput = readvals(s,4,values); 
					if (validinput) {

						// YOUR CODE FOR HW 2 HERE. 
						// values[0..2] are the axis, values[3] is the angle.  
						// You may want to normalize the axis (or in Transform::rotate)
						// See how the stack is affected, as above.  
						// Note that rotate returns a mat3. 
						// Also keep in mind what order your matrix is!
						vec3 axis(values[0], values[1], values[2]);
						axis = glm::normalize(axis);
						mat3 rot = Transform::rotate(values[3], axis);
						mat4 rot4(rot);
						rightmultiply(rot4, transfstack);
					}
				}

				// I include the basic push/pop code for matrix stacks
				else if (cmd == "pushTransform") {
					transfstack.push(transfstack.top()); 
				} else if (cmd == "popTransform") {
					if (transfstack.size() <= 1) {
						cerr << "Stack has no elements.  Cannot Pop\n"; 
					} else {
						transfstack.pop(); 
					}
				}

				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n"; 
				}
			}
			getline (in, str); 
		}

		//eye = eyeinit; 
		//up = upinit; 
		sx = sy = 1.0;  // keyboard controlled scales in x and y 
		tx = ty = 0.0;  // keyboard controllled translation in x and y 

	} else {
		cerr << "Unable to Open Input Data File " << filename << "\n"; 
		throw 2; 
	}
}

const int BITPERPIXEL = 24;

struct Ray 
{
	Ray(vec3 origin, vec3 dir)
		:_origin(origin),_direction(dir) {}
	Ray(){}
	vec3 _origin;
	vec3 _direction;
};

struct Camera
{
	Camera(){}
	vec3 _eye;
	vec3 _up;
	vec3 _center;
	float _fovy, _fovx;
	vec3 _w, _u, _v;
	void orthogonalize()
	{
		_w = glm::normalize(_eye - _center);
		_u = glm::normalize(glm::cross(_up, _w));
		_v = glm::cross(_w, _u);
	}
};

struct Scene 
{
	Scene(object* objects, int objnum){}
	object _objects[maxobjects];
	int _maxobjnum;
	int _objnum;
};

struct IntersectionInfo
{
	IntersectionInfo(float dist, object * obj)
		: _dist(dist), _object(obj){}
	float _dist;
	object *_object;
};

Ray RayThruPixel(const Camera &cam, int i, int j, int width, int height)
{
	float alpha = tan(cam._fovx / 2) * (j - width / 2) / (width / 2);
	float beta = tan(cam._fovy / 2) * (height / 2 - i) / (height / 2);
	Ray ray;
	ray._origin = cam._eye;
	ray._direction = glm::normalize(vec3(alpha, beta, -1));
	return ray;
}

bool IntersectWithTri(const Ray& ray, const object &obj, float &dist)
{
	//重心法
	
}

IntersectionInfo Intersection(const Ray& ray, const Scene& scene)
{
	float mindist = FLT_MAX;
	object *hitobj;
	for (int i = 0; i < scene._objnum; i++)
	{
		if (scene._objects[i].type == tri)
		{
			float dist = 0.f;
			if (IntersectWithTri(ray, scene._objects[i], dist))
			{

			}
			else
			{

			}
		}
	}
	return IntersectionInfo(mindist, hitobj);
}

RGBQUAD FindColor(IntersectionInfo hitinfo)
{
	RGBQUAD color;
	return color;
}

FIBITMAP* Raytrace(const Camera &cam, const Scene &scene, int width, int height)
{
	FIBITMAP *bitmap = FreeImage_Allocate(width, height, BITPERPIXEL);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Ray ray = RayThruPixel(cam, i, j, width, height);

			IntersectionInfo hitinfo= Intersection(ray, scene);
			RGBQUAD color = FindColor(hitinfo);
			FreeImage_SetPixelColor(bitmap,i,j,&color);
		}
	}

	return bitmap;
}

int main(int argc, char* argv[]) {
// 	if (argc < 2) {
// 		cerr << "Usage: transforms scenefile [grader input (optional)]\n"; 
// 		exit(-1); 
// 	}

	//read test file
	//readfile(argv[1]);

	const int WIDTH = 100;
	const int HEIGHT = 100;

	FreeImage_Initialise();

	Camera cam;
	cam._eye = eyeinit; cam._center = center; cam._up = upinit; 
	cam._fovy = fovy; cam._fovx = w * fovy / h;
	cam.orthogonalize();
	Scene scene(objects, numobjects);

	FIBITMAP *bitmap = Raytrace(cam, scene, w, h);

	FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);

	FreeImage_DeInitialise();
	return 0;
}
