// Readfile definitions 

#include "Transform.h"

using namespace std;

vec3 eyeinit;
vec3 upinit ; 
vec3 center ;
int w, h ; 
float fovy ;

static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {cube, sphere, teapot} ;
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

// For multiple objects, read from a file.  
const int maxobjects = 10 ; 
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
} objects[maxobjects] ;

void matransform (stack<mat4> &transfstack, float * values) ;
void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename) ;
