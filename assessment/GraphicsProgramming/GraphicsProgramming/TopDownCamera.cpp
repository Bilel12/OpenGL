#include "TopDownCamera.h"

TopDownCamera::TopDownCamera() {
	position.setX(0.f);
	position.setY(15.f);
	position.setZ(0.f);
	forward.setX(0.0f);
	forward.setY(0.0f);
	forward.setZ(0.0f);
	up.setX(0.0f);
	up.setY(0.0f);
	up.setZ(1.0f);
	side.setX(0.0f);
	side.setY(2.0f);
	side.setZ(1.0f);
	setPitch(-90.0f);
	update();
}

TopDownCamera::~TopDownCamera() {}


void TopDownCamera::update() {
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
	// Calculate forward vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;
	// Calculate lookAt vector
	lookAt.x = position.x + forward.x;
	lookAt.y = position.y + forward.y;
	lookAt.z = position.z + forward.z;
	// Calculate up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	// Calculate side Vector (right)
	side = forward.cross(up); // this is a cross product between the forward and up vector
}

float TopDownCamera::getPositionX() {
	return position.getX();
}
float TopDownCamera::getPositionY() {
	return position.getY();
}
float TopDownCamera::getPositionZ() {
	return position.getZ();
}

float TopDownCamera::getForwardX() {
	return forward.getX();
}
float TopDownCamera::getForwardY() {
	return forward.getY();
}
float TopDownCamera::getForwardZ() {
	return forward.getZ();
}

float TopDownCamera::getLookAtX() {
	return lookAt.getX();
}
float TopDownCamera::getLookAtY() {
	return lookAt.getY();
}
float TopDownCamera::getLookAtZ() {
	return lookAt.getZ();
}

float TopDownCamera::getUpX() {
	return up.getX();
}
float TopDownCamera::getUpY() {
	return up.getY();
}
float TopDownCamera::getUpZ() {
	return up.getZ();
}

float TopDownCamera::getSideX() {
	return side.getZ();
}
float TopDownCamera::getSideY() {
	return side.getY();
}
float TopDownCamera::getSideZ() {
	return side.getX();
}

float TopDownCamera::getYaw() {
	return Yaw;
}
float TopDownCamera::getPitch() {
	return Pitch;
}
float TopDownCamera::getRoll() {
	return Roll;
}

void TopDownCamera::setYaw(float arg) {
	Yaw = arg;
}
void TopDownCamera::setPitch(float arg) {
	Pitch = arg;
}
void TopDownCamera::setRoll(float arg) {
	Roll = arg;
}

void TopDownCamera::moveForward(float dt) {
	position.add(forward, dt);
}
void TopDownCamera::moveBackwards(float dt) {
	position.subtract(forward, dt);
}

void TopDownCamera::moveUp(float dt) {
	position.add(up, dt);
}
void TopDownCamera::moveDown(float dt) {
	position.subtract(up, dt);
}

void TopDownCamera::moveSideLeft(float dt) {
	position.subtract(side, dt);
}

void TopDownCamera::moveSideRight(float dt) {
	position.add(side, dt);
}

void TopDownCamera::addYaw(float dt, float value) {
	Yaw += value * dt;
}
void TopDownCamera::subtractYaw(float dt, float value) {
	Yaw -= value * dt;
}
void TopDownCamera::addPitch(float dt, float value) {
	Pitch += value * dt;
}
void TopDownCamera::subtractPitch(float dt, float value) {
	Pitch -= value * dt;
}
void TopDownCamera::addRoll(float dt, float value) {
	Roll += value * dt;
}
void TopDownCamera::subtractRoll(float dt, float value) {
	Roll -= value * dt;
}

void TopDownCamera::updateYaw(int width, int mouseX, int speed) {
	Yaw += static_cast<float>((mouseX - (width / 2)) / speed);
}
void TopDownCamera::updatePitch(int height, int mouseY, int speed) {
	Pitch -= static_cast<float>((mouseY - (height / 2)) / speed);
}

void TopDownCamera::cameraControll(float dt, int width, int height, Input *input) {
	// move camera forward
	if (input->isKeyDown('w') || input->isKeyDown('W')) {
		moveUp(dt);
	}
	// move camera backwards
	if (input->isKeyDown('s') || input->isKeyDown('S')) {
		moveDown(dt);
	}
	// move camera to the left
	if (input->isKeyDown('a') || input->isKeyDown('A')) {
		moveSideLeft(dt);
	}
	// move camera to the right
	if (input->isKeyDown('d') || input->isKeyDown('D')) {
		moveSideRight(dt);
	}
	// move camera down
	//if (input->isKeyDown(GLUT_KEY_UP) || input->isKeyDown('r') || input->isKeyDown('R')) {
	//	
	//}
	//// move camera down
	//if (input->isKeyDown(GLUT_KEY_DOWN) || input->isKeyDown('f') || input->isKeyDown('F')) {
	//	
	//}
	glutWarpPointer(width / 2, height / 2);
}

