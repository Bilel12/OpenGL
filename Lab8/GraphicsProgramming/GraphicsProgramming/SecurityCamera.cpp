#include "SecurityCamera.h"



SecurityCamera::SecurityCamera() {
	position.setX(4.0f);
	position.setY(4.0f);
	position.setZ(6.0f);
	forward.setX(0.0f);
	forward.setY(0.0f);
	forward.setZ(0.0f);
	up.setX(0.0f);
	up.setY(0.0f);
	up.setZ(1.0f);
	side.setX(0.0f);
	side.setY(2.0f);
	side.setZ(1.0f);

	update();
}

SecurityCamera::~SecurityCamera() {}

void SecurityCamera::update() {
	float cosR, cosP, cosY;	//temp values for sin/cos from 
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the FreeCamera

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
	lookAt.x = position.x + forward.x;
	lookAt.y = position.y + forward.y;
	lookAt.z = position.z + forward.z;

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	side = forward.cross(up); // this is a cross product between the forward and up vector. 
							  // If you don’t need to calculate this,  don’t do it. 
}

float SecurityCamera::getPositionX() {
	return position.getX();
}
float SecurityCamera::getPositionY() {
	return position.getY();
}
float SecurityCamera::getPositionZ() {
	return position.getZ();
}

float SecurityCamera::getForwardX() {
	return forward.getX();
}
float SecurityCamera::getForwardY() {
	return forward.getY();
}
float SecurityCamera::getForwardZ() {
	return forward.getZ();
}

float SecurityCamera::getLookAtX() {
	return lookAt.getX();
}
float SecurityCamera::getLookAtY() {
	return lookAt.getY();
}
float SecurityCamera::getLookAtZ() {
	return lookAt.getZ();
}

float SecurityCamera::getUpX() {
	return up.getX();
}
float SecurityCamera::getUpY() {
	return up.getY();
}
float SecurityCamera::getUpZ() {
	return up.getZ();
}

float SecurityCamera::getYaw() {
	return side.getX();
}
float SecurityCamera::getPitch() {
	return side.getY();
}
float SecurityCamera::getRoll() {
	return side.getZ();
}

void SecurityCamera::setYaw(float arg) {
	Yaw = arg;
}
void SecurityCamera::setPitch(float arg) {
	Pitch = arg;
}
void SecurityCamera::setRoll(float arg) {
	Roll = arg;
}

void SecurityCamera::moveForward(float dt) {
	position.add(forward, dt);
}
void SecurityCamera::moveBackwards(float dt) {
	position.subtract(forward, dt);
}

void SecurityCamera::moveUp(float dt) {
	position.add(up, dt);
}
void SecurityCamera::moveDown(float dt) {
	position.subtract(up, dt);
}

void SecurityCamera::moveSideLeft(float dt) {
	position.subtract(side, dt);
}

void SecurityCamera::moveSideRight(float dt) {
	position.add(side, dt);
}

void SecurityCamera::addYaw(float dt) {
	Yaw += 1 * dt;
}
void SecurityCamera::subtractYaw(float dt) {
	Yaw -= 1 * dt;
}
void SecurityCamera::addPitch(float dt) {
	Pitch += 1 * dt;
}
void SecurityCamera::subtractPutch(float dt) {
	Pitch -= 1 * dt;
}
void SecurityCamera::addRoll(float dt) {
	Roll += 1 * dt;
}
void SecurityCamera::subtractroll(float dt) {
	Roll -= 1 * dt;
}

void SecurityCamera::updateYaw(int width, int mouseX, int speed) {
	Yaw += static_cast<float>((mouseX - (width / 2)) / speed);
}
void SecurityCamera::updatePitch(int height, int mouseY, int speed) {
	Pitch -= static_cast<float>((mouseY - (height / 2)) / speed);
}

void SecurityCamera::userControll(float dt, int width, int height) {
	return;
}