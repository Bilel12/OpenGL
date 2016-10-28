#include "FreeCamera.h"

FreeCamera::FreeCamera() {
	position.setX(0.0f);
	position.setY(0.0f);
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

FreeCamera::~FreeCamera() {}

void FreeCamera::update() {
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

float FreeCamera::getPositionX() {
	return position.getX();
}
float FreeCamera::getPositionY() {
	return position.getY();
}
float FreeCamera::getPositionZ() {
	return position.getZ();
}

float FreeCamera::getForwardX() {
	return forward.getX();
}
float FreeCamera::getForwardY() {
	return forward.getY();
}
float FreeCamera::getForwardZ() {
	return forward.getZ();
}

float FreeCamera::getLookAtX() {
	return lookAt.getX();
}
float FreeCamera::getLookAtY() {
	return lookAt.getY();
}
float FreeCamera::getLookAtZ() {
	return lookAt.getZ();
}

float FreeCamera::getUpX() {
	return up.getX();
}
float FreeCamera::getUpY() {
	return up.getY();
}
float FreeCamera::getUpZ() {
	return up.getZ();
}

float FreeCamera::getSideX() {
	return side.getZ();
}
float FreeCamera::getSideY() {
	return side.getY();
}
float FreeCamera::getSideZ() {
	return side.getX();
}

float FreeCamera::getYaw() {
	return Yaw;
}
float FreeCamera::getPitch() {
	return Pitch;
}
float FreeCamera::getRoll() {
	return Roll;
}

void FreeCamera::setYaw(float arg) {
	Yaw = arg;
}
void FreeCamera::setPitch(float arg) {
	Pitch = arg;
}
void FreeCamera::setRoll(float arg) {
	Roll = arg;
}

void FreeCamera::moveForward(float dt) {
	position.add(forward, dt);
}
void FreeCamera::moveBackwards(float dt) {
	position.subtract(forward, dt);
}

void FreeCamera::moveUp(float dt) {
	position.add(up, dt);
}
void FreeCamera::moveDown(float dt) {
	position.subtract(up, dt);
}

void FreeCamera::moveSideLeft(float dt) {
	position.subtract(side, dt);
}

void FreeCamera::moveSideRight(float dt) {
	position.add(side, dt);
}

void FreeCamera::addYaw(float dt) {
	Yaw += 1 * dt;
}
void FreeCamera::subtractYaw(float dt) {
	Yaw -= 1 * dt;
}
void FreeCamera::addPitch(float dt) {
	Pitch += 1 * dt;
}
void FreeCamera::subtractPitch(float dt) {
	Pitch -= 1 * dt;
}
void FreeCamera::addRoll(float dt) {
	Roll += 1 * dt;
}
void FreeCamera::subtractRoll(float dt) {
	Roll -= 1 * dt;
}

void FreeCamera::updateYaw(int width, int mouseX, int speed) {
	Yaw += static_cast<float>((mouseX - (width / 2)) / speed);
}
void FreeCamera::updatePitch(int height, int mouseY, int speed) {
	Pitch -= static_cast<float>((mouseY - (height / 2)) / speed);
}

void FreeCamera::userControll(float dt, int width, int height, Input *input) {
	// move camera forward
	if (input->isKeyDown('w') || input->isKeyDown('w')) {
		moveForward(dt);
	}
	// move camera backwards
	if (input->isKeyDown('s') || input->isKeyDown('S')) {
		moveBackwards(dt);
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
	if (input->isKeyDown(GLUT_KEY_UP) || input->isKeyDown('r') || input->isKeyDown('R')) {
		moveUp(dt);
	}
	// move camera down
	if (input->isKeyDown(GLUT_KEY_DOWN) || input->isKeyDown('f') || input->isKeyDown('F')) {
		moveDown(dt);
	}
	// camera's Yaw mouse controll, last variable controlls speed
	updateYaw(width, input->getMouseX(), 2);
	// camera's Pitch mouse controll, last variable controlls speed
	updatePitch(height, input->getMouseY(), 2);
	// Force mouse to return to the centre of the window
	glutWarpPointer(width / 2, height / 2);
}

void FreeCamera::cameraControll(float dt, int width, int height) {
	return;
}
