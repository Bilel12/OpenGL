#include "FPPCamera.h"

FPPCamera::FPPCamera() {
	position.set(0.0f, 0.0f, 6.0f);
	forward.set(0.0f, 0.0f, 0.0f);
	up.set(0.0f, 0.0f, 0.0f);
	side.set(0.0f, 0.0f, 0.0f);
	lookAt.set(1.0f, 1.0f, 5.0f);
	setYaw(0);
	setPitch(0);
	setRoll(0);
	// Security camera settings
	camera_speed = 0.5f;
	clamp_value = Yaw;
	bottomClamp = Pitch + (-40.f), topClamp = Pitch + (40.f);
	update();
}

FPPCamera::~FPPCamera() {}

void FPPCamera::update() {
	float cosR, cosP, cosY;	//temp values for sin/cos from 
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the FPPCamera
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

float FPPCamera::getPositionX() {
	return position.getX();
}
float FPPCamera::getPositionY() {
	return position.getY();
}
float FPPCamera::getPositionZ() {
	return position.getZ();
}

float FPPCamera::getForwardX() {
	return forward.getX();
}
float FPPCamera::getForwardY() {
	return forward.getY();
}
float FPPCamera::getForwardZ() {
	return forward.getZ();
}

float FPPCamera::getLookAtX() {
	return lookAt.getX();
}
float FPPCamera::getLookAtY() {
	return lookAt.getY();
}
float FPPCamera::getLookAtZ() {
	return lookAt.getZ();
}

float FPPCamera::getUpX() {
	return up.getX();
}
float FPPCamera::getUpY() {
	return up.getY();
}
float FPPCamera::getUpZ() {
	return up.getZ();
}

float FPPCamera::getSideX() {
	return side.getZ();
}
float FPPCamera::getSideY() {
	return side.getY();
}
float FPPCamera::getSideZ() {
	return side.getX();
}

float FPPCamera::getYaw() {
	return Yaw;
}
float FPPCamera::getPitch() {
	return Pitch;
}
float FPPCamera::getRoll() {
	return Roll;
}

void FPPCamera::setLookAtX(float x) {
	lookAt.setX(x);
}
void FPPCamera::setLookAtY(float y) {
	lookAt.setY(y);
}
void FPPCamera::setLookAtZ(float z) {
	lookAt.setZ(z);
}

void FPPCamera::setYaw(float arg) {
	Yaw = arg;
}
void FPPCamera::setPitch(float arg) {
	Pitch = arg;
}
void FPPCamera::setRoll(float arg) {
	Roll = arg;
}

void FPPCamera::moveForward(float dt) {
	position.add(forward, dt);
}
void FPPCamera::moveBackwards(float dt) {
	position.subtract(forward, dt);
}

void FPPCamera::moveUp(float dt) {
	position.add(up, dt);
}
void FPPCamera::moveDown(float dt) {
	position.subtract(up, dt);
}

void FPPCamera::moveSideLeft(float dt) {
	position.subtract(side, dt);
}

void FPPCamera::moveSideRight(float dt) {
	position.add(side, dt);
}

void FPPCamera::addYaw(float dt, float value) {
	Yaw += value * dt;
}
void FPPCamera::subtractYaw(float dt, float value) {
	Yaw -= value * dt;
}
void FPPCamera::addPitch(float dt, float value) {
	Pitch += value * dt;
}
void FPPCamera::subtractPitch(float dt, float value) {
	Pitch -= value * dt;
}
void FPPCamera::addRoll(float dt, float value) {
	Roll += value * dt;
}
void FPPCamera::subtractRoll(float dt, float value) {
	Roll -= value * dt;
}

void FPPCamera::updateYaw(int width, int mouseX, int speed) {
	Yaw += static_cast<float>((mouseX - (width / 2)) / speed);
}
void FPPCamera::updatePitch(int height, int mouseY, int speed) {
		Pitch -= static_cast<float>((mouseY - (height / 2)) / speed);
}

void FPPCamera::cameraControll(float dt, int width, int height, Input *input) {
	// move camera forward
	if (input->isKeyDown('w') || input->isKeyDown('W')) {
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
	// camera's Yaw mouse controll, last variable controlls speed
	updateYaw(width, input->getMouseX(), 2);
	// camera's Pitch mouse controll, last variable controlls speed
	if (Pitch <= topClamp && Pitch >= bottomClamp) {
		updatePitch(height, input->getMouseY(), 2);
	}
	// Force mouse to return to the centre of the window
	glutWarpPointer(width / 2, height / 2);
}
