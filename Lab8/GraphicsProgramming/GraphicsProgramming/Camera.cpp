#include "Camera.h"

//Camera::~Camera()
//{
//}

//Camera::Camera()
//{
//	position.setX(0.0f);
//	position.setY(0.0f);
//	position.setZ(6.0f);
//	forward.setX(0.0f);
//	forward.setY(0.0f);
//	forward.setZ(0.0f);
//	up.setX(0.0f);
//	up.setY(0.0f);
//	up.setZ(1.0f);
//	side.setX(0.0f);
//	side.setY(2.0f);
//	side.setZ(1.0f);
//	update();
//}



//void Camera::update() {
//	float cosR, cosP, cosY;	//temp values for sin/cos from 
//	float sinR, sinP, sinY;
//	// Roll, Pitch and Yall are variables stored by the camera
//
//	// handle rotation
//
//
//	// Only want to calculate these values once, when rotation changes, not every frame. 
//	cosY = cosf(Yaw*3.1415 / 180);
//	cosP = cosf(Pitch*3.1415 / 180);
//	cosR = cosf(Roll*3.1415 / 180);
//	sinY = sinf(Yaw*3.1415 / 180);
//	sinP = sinf(Pitch*3.1415 / 180);
//	sinR = sinf(Roll*3.1415 / 180);
//
//	//This using the parametric equation of a sphere
//
//	// Calculate the three vectors to put into  glu Lookat
//
//	// Look direction,  position and the up vector 
//
//	// This function could also calculate the right vector
//
//	forward.x = sinY * cosP;
//	forward.y = sinP;
//	forward.z = cosP * -cosY;
//
//	// Look At Point
//	lookAt.x = position.x + forward.x;
//	lookAt.y = position.y + forward.y;
//	lookAt.z = position.z + forward.z;	
//
//	// Up Vector
//	up.x = -cosY * sinR - sinY * sinP * cosR;
//	up.y = cosP * cosR;
//	up.z = -sinY * sinR - sinP * cosR * -cosY;
//
//	// Side Vector (right)
//	side = forward.cross(up); // this is a cross product between the forward and up vector. 
//							  // If you don’t need to calculate this,  don’t do it. 
//}
//
//float Camera::getPositionX() {
//	return position.getX();
//}
//float Camera::getPositionY() {
//	return position.getY();
//}
//float Camera::getPositionZ() {
//	return position.getZ();
//}
//
//float Camera::getForwardX() {
//	return forward.getX();
//}
//float Camera::getForwardY() {
//	return forward.getY();
//}
//float Camera::getForwardZ() {
//	return forward.getZ();
//}
//
//float Camera::getLookAtX() {
//	return lookAt.getX();
//}
//float Camera::getLookAtY() {
//	return lookAt.getY();
//}
//float Camera::getLookAtZ() {
//	return lookAt.getZ();
//}
//
//float Camera::getUpX() {
//	return up.getX();
//}
//float Camera::getUpY() {
//	return up.getY();
//}
//float Camera::getUpZ() {
//	return up.getZ();
//}
//
//float Camera::getYaw() {
//	return side.getX();
//}
//float Camera::getPitch() {
//	return side.getY();
//}
//float Camera::getRoll() {
//	return side.getZ();
//}
//
//void Camera::moveForward(float dt){
//	position.add(forward, dt);
//}
//void Camera::moveBackwards(float dt) {
//	position.subtract(forward, dt);
//}
//
//void Camera::moveUp(float dt) {
//	position.add(up, dt);
//}
//void Camera::moveDown(float dt) {
//	position.subtract(up, dt);
//}
//
//void Camera::moveSideLeft(float dt) {
//	position.subtract(side, dt);
//}
//
//void Camera::moveSideRight(float dt) {
//	position.add(side, dt);
//}
//
//void Camera::addYaw(float dt) {
//	Yaw += 1 * dt;
//}
//void Camera::subtractYaw(float dt) {
//	Yaw -= 1 * dt;
//}
//void Camera::addPitch(float dt) {
//	Pitch += 1 * dt;
//}
//void Camera::subtractPutch(float dt) {
//	Pitch -= 1 * dt;
//}
//void Camera::addRoll(float dt) {
//	Roll += 1 * dt;
//}
//void Camera::subtractroll(float dt) {
//	Roll -= 1 * dt;
//}
//
//void Camera::getMousePositionX(int width, int mouseX, int speed) {
//	Yaw += static_cast<float>((mouseX - (width / 2)) / speed);
//}
//void Camera::getMousePositionY(int height, int mouseY, int speed) {
//	Pitch -= static_cast<float>((mouseY - (height / 2)) / speed);
//}
