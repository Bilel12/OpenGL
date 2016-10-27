#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
public:
	//Camera();
	virtual ~Camera() {}
	virtual void update() = 0;
	virtual void moveForward(float dt) = 0;
	virtual void moveBackwards(float dt) = 0;
	virtual void moveUp(float dt) = 0;
	virtual void moveDown(float dt) = 0;
	virtual void moveSideLeft(float dt) = 0;
	virtual void moveSideRight(float dt) = 0;

	virtual void addYaw(float dt) = 0;
	virtual void subtractYaw(float dt) = 0;
	virtual void addPitch(float dt) = 0;
	virtual void subtractPutch(float dt) = 0;
	virtual void addRoll(float dt) = 0;
	virtual void subtractroll(float dt) = 0;

	virtual float getPositionX() = 0;
	virtual float getPositionY() = 0;
	virtual float getPositionZ() = 0;

	virtual float getForwardX() = 0;
	virtual float getForwardY() = 0;
	virtual float getForwardZ() = 0;

	virtual float getLookAtX() = 0;
	virtual float getLookAtY() = 0;
	virtual float getLookAtZ() = 0;

	virtual float getUpX() = 0;
	virtual float getUpY() = 0;
	virtual float getUpZ() = 0;

	virtual float getYaw() = 0;
	virtual float getPitch() = 0;
	virtual float getRoll() = 0;

	virtual void updateYaw(int width, int mouseX, int speed) = 0;
	virtual void updatePitch(int height, int mouseY, int speed) = 0;
};

#endif 

