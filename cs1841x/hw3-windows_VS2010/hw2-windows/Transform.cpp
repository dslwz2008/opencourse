// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1.  
	float rad = glm::radians(degrees);
	mat3 matA(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
		);
	mat3 matB(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.z, axis.y*axis.z, axis.z*axis.z
		);
	mat3 matC(
		0.0, axis.z, -axis.y,
		-axis.z, 0.0, axis.x,
		axis.y, -axis.x, 0.0
		);
	mat3 rot = cos(rad) * matA + (1-cos(rad))*matB + sin(rad)*matC;
	// You will change this return call
	return rot;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.
	mat3 rotateMat = Transform::rotate(degrees, glm::normalize(up));
	eye = rotateMat*eye;
	up = rotateMat*up;
	//eye = rotate(degrees, up)*eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
	// Likely the same as in HW 1.
	mat3 rotateMat = Transform::rotate(degrees, glm::normalize(glm::cross(eye, up)));
	up = rotateMat*up;
	eye = rotateMat*eye;
	//vec3 right=glm::normalize(glm::cross(-eye, up));
	//eye = rotate(-degrees, right) * eye;
	//up = rotate(-degrees, right) * up; 
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1. 
	//construct the coordinate frame
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 rotateMat = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 eyeMat = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);
	mat4 resultMat = rotateMat*eyeMat;


	// You will change this return call
	return resultMat;

	//vec3 x = glm::cross(up,eye-center); 
	//vec3 y = glm::cross(eye-center,x); 
	//vec3 ret = glm::normalize(y); 

	//vec3 w = glm::normalize(eye-center);
	//vec3 u = glm::normalize(glm::cross(ret,w));
	//vec3 v = glm::normalize(glm::cross(w,u));
	//mat4 t(
	//	1.0, 0.0, 0.0, 0.0,
	//	0.0, 1.0, 0.0, 0.0,
	//	0.0, 0.0, 1.0, 0.0,
	//	-eye.x, -eye.y, -eye.z, 1.0
	//	);
	//mat4 r(
	//	u.x, v.x, w.x, 0.0,
	//	u.y, v.y, w.y, 0.0,
	//	u.z, v.z, w.z, 0.0,
	//	0.0, 0.0, 0.0, 1.0
	//	);
 //   return r*t;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    // YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  
	mat4 ret(0.f);
	float range = tan(glm::radians(fovy / 2.f)) * zNear;
	//近平面上4个角点
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	ret[0][0] = (2.f * zNear) / (right - left);
	ret[1][1] = (2.f * zNear) / (top - bottom);
	ret[2][2] = - (zFar + zNear) / (zFar - zNear);
	ret[2][3] = - 1.f;
	ret[3][2] = - (2.f * zFar * zNear) / (zFar - zNear);
	
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	mat4 ret = mat4(
		sx, 0, 0, 0,
		0, sy, 0, 0, 
		0, 0, sz, 0, 
		0, 0, 0, 1);
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	ret = mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		tx, ty, tz, 1);
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
