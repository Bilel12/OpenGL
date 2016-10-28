#ifndef _FREECAMERA_H_
#define _FREECAMERA_H_

#include <glut.h>
#include "Input.h"
#include "Camera.h"

class FreeCamera : public Camera
{
public:
	FreeCamera();
	~FreeCamera();

	virtual void update();
	virtual void moveForward(float dt);
	virtual void moveBackwards(float dt);
	virtual void moveUp(float dt);
	virtual void moveDown(float dt);
	virtual void moveSideLeft(float dt);
	virtual void moveSideRight(float dt);

	virtual void addYaw(float dt);
	virtual void subtractYaw(float dt);
	virtual void addPitch(float dt);
	virtual void subtractPutch(float dt);
	virtual void addRoll(float dt);
	virtual void subtractroll(float dt);

	virtual float getPositionX();
	virtual float getPositionY();
	virtual float getPositionZ();

	virtual float getForwardX();
	virtual float getForwardY();
	virtual float getForwardZ();

	virtual float getLookAtX();
	virtual float getLookAtY();
	virtual float getLookAtZ();

	virtual float getUpX();
	virtual float getUpY();
	virtual float getUpZ();

	virtual float getYaw();
	virtual float getPitch();
	virtual float getRoll();

	virtual void updateYaw(int width, int mouseX, int speed);
	virtual void updatePitch(int height, int mouseY, int speed);

	virtual void userControll(float dt, int width, int height, Input *input);
	virtual void cameraControll(float dt, int width, int height);
private:
	Vector3 position;
	Vector3 lookAt;
	Vector3 forward;
	Vector3 up;
	Vector3 side;
	float Yaw, Pitch, Roll;
};

#endif
