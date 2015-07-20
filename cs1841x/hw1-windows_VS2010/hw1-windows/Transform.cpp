// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
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

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = rotate(degrees, up)*eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	vec3 right=glm::normalize(glm::cross(-eye, up));
	eye = rotate(-degrees, right) * eye;
	up = rotate(-degrees, right) * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 x = glm::cross(up,eye); 
	vec3 y = glm::cross(eye,x); 
	vec3 ret = glm::normalize(y); 

	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(ret,w));
	vec3 v = glm::normalize(glm::cross(w,u));
	mat4 t(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		-eye.x, -eye.y, -eye.z, 1.0
		);
	mat4 r(
		u.x, v.x, w.x, 0.0,
		u.y, v.y, w.y, 0.0,
		u.z, v.z, w.z, 0.0,
		0.0, 0.0, 0.0, 1.0
		);
  // You will change this return call
  return r*t;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  
	float range = tan(glm::radians(fovy / 2.f)) * zNear;
	//近平面上4个角点
	float left = -range * aspect;
	float right = range * aspect;
	float bottom = -range;
	float top = range;

	mat4 ret(0.f);
	ret[0][0] = (2.f * zNear) / (right - left);
	ret[1][1] = (2.f * zNear) / (top - bottom);
	ret[2][2] = - (zFar + zNear) / (zFar - zNear);
	ret[2][3] = - 1.f;
	ret[3][2] = - (2.f * zFar * zNear) / (zFar - zNear);

	return ret;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
