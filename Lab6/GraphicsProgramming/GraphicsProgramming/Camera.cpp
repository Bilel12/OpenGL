#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update() {
	float cosR, cosP, cosY;	//temp values for sin/cos from 
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the camera

	// handle rotation

	// Only want to calculate these values once, when rotation changes, not every frame. 
	cosY = cosf(Yaw*3.1415 / 180);
	cosP = cosf(Pitch*3.1415 / 180);
	cosR = cosf(Roll*3.1415 / 180);
	sinY = sinf(Yaw*3.1415 / 180);
	sinP = sinf(Pitch*3.1415 / 180);
	sinR = sinf(Roll*3.1415 / 180);

	//This using the parametric equation of a sphere

	// Calculate the three vectors to put into  glu Lookat

	// Look direction,  position and the up vector 

	// This function could also calculate the right vector

	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.	

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)


	// this is a cross product between the forward and up vector. 
	// If you don’t need to calculate this,  don’t do it. 
	//lookat = position + forward
}

float Camera::getForwardX() {
	return forward.getX();
}

float Camera::getForwardY() {
	return forward.getY();
}

float Camera::getForwardZ() {
	return forward.getZ();
}

float Camera::getUpX() {
	return up.getX();
}

float Camera::getUpY() {
	return up.getY();
}

float Camera::getUpZ() {
	return up.getZ();
}

float Camera::getYaw() {
	return forward.getX();
}

float Camera::getPitch() {
	return forward.getY();
}

float Camera::getRoll() {
	return forward.getZ();
}
