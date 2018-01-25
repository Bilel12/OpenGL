#include "SecurityCamera.h"

SecurityCamera::SecurityCamera() {
	position = (Vector3(7.5f, 6.0f, 8.0f));
	forward = (Vector3(0.0f, 0.0f, 0.0f));
	up = (Vector3(0.0f, 0.0f, 1.0f));
	side = (Vector3(0.0f, 2.0f, 1.0f));
	setYaw(-65.0f);
	setPitch(-35.0f);
	// Security camera settings
	camera_speed = 0.5f;
	clamp_value = Yaw;
	leftClamp = Yaw + (-40.f), rightClamp = Yaw + (40.f);
	lerpRight = true, stop_camera = false;
	update();
}

SecurityCamera::~SecurityCamera() {}

void SecurityCamera::update() {
	float cosR, cosP, cosY;	//temp values for sin/cos from 
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the FreeCamera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame. 
	cosY = cosf( (Yaw*3.1415f) / 180.0f);
	cosP = cosf( (Pitch*3.1415f) / 180.0f);
	cosR = cosf( (Roll*3.1415f) / 180.0f);
	sinY = sinf( (Yaw*3.1415f) / 180.0f);
	sinP = sinf( (Pitch*3.1415f) / 180.0f);
	sinR = sinf( (Roll*3.1415f) / 180.0f);
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
	return Yaw;
}
float SecurityCamera::getPitch() {
	return Pitch;
}
float SecurityCamera::getRoll() {
	return Roll;
}

float SecurityCamera::getSideX() {
	return side.getZ();
}
float SecurityCamera::getSideY() {
	return side.getY();
}
float SecurityCamera::getSideZ() {
	return side.getX();
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

void SecurityCamera::addYaw(float dt, float value) {
	Yaw += value * dt;
}
void SecurityCamera::subtractYaw(float dt, float value) {
	Yaw -= value * dt;
}
void SecurityCamera::addPitch(float dt, float value) {
	Pitch += value * dt;
}
void SecurityCamera::subtractPitch(float dt, float value) {
	Pitch -= value * dt;
}
void SecurityCamera::addRoll(float dt, float value) {
	Roll += value * dt;
}
void SecurityCamera::subtractRoll(float dt, float value) {
	Roll -= value * dt;
}

void SecurityCamera::updateYaw(int width, int mouseX, int speed) {
	Yaw += static_cast<float>((mouseX - (width / 2)) / speed);
}
void SecurityCamera::updatePitch(int height, int mouseY, int speed) {
	Pitch += static_cast<float>((mouseY - (height / 2)) / speed);
}

void SecurityCamera::cameraControll(float dt, int width, int height, Input *input) {
	// move camera forward
	if (input->isKeyDown('w') || input->isKeyDown('W')) {
		if (Pitch <= rightClamp) { addPitch(dt, camera_speed + 1.f); }	// use right clamping value to clamp up pitch movemnt
	}
	// move camera backwards
	if (input->isKeyDown('s') || input->isKeyDown('S')) {
		if (Pitch >= leftClamp) { subtractPitch(dt, camera_speed + 1.f); } // use left clamping value to clamp down pitch movemnt
	}
	// move camera to the left
	if (input->isKeyDown('a') || input->isKeyDown('A')) {
		if (Yaw >= leftClamp) {
			subtractYaw(dt, camera_speed + 1.f);
			clamp_value = Yaw;
		}
	}
	// move camera to the right
	if (input->isKeyDown('d') || input->isKeyDown('D')) {
		if (Yaw <= rightClamp) { 
			addYaw(dt, camera_speed + 1.f); 
			clamp_value = Yaw;
		}
	}
	// toggle camera's automatic movemnt
	if (input->isKeyDown('c') || input->isKeyDown('C')) {
		stop_camera = !stop_camera;
		input->SetKeyUp('c'); input->SetKeyUp('C');
	}
	// move camera procedurally
	// set yaw based on a clamp value
	// start lerping right
	if (!stop_camera) { // check if camera's movement is enabled
		if (lerpRight) {// lerp right
			clamp_value += camera_speed * dt;	// set clamp value based on camera's speed and delta time (add to 'clamp_value' - 'camera_speed' value multiplied by 'delta time')
			setYaw(clamp_value);				// use clamp value to set camera's yaw
			if (clamp_value >= rightClamp) {	// if clamp value is greater than or equal right clamping value stop lerping right and lerp left
				lerpRight = false;
			}
		} else {	// lerp left
			clamp_value -= camera_speed * dt;	// set clamp value based on camera's speed and delta time (subtrack from 'clamp_value', 'camera_speed' value multiplied by 'delta time') 
			setYaw(clamp_value);				// use clamp value to set camera's yaw
			if (clamp_value <= leftClamp) {		// if clamp value is less than or equal right clamping value stop lerping left and lerp right
				lerpRight = true;
			}
		}
	}
	//// keep mouse cursor in the middle of the screen
	//glutWarpPointer(width / 2, height / 2);
}

