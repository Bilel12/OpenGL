#ifndef _SECURITYCAMERA_H
#define _SECURITYCAMERA_H

#include "glut.h"
#include "Input.h"
#include "Camera.h"
#include "Window.h"

class SecurityCamera : public Camera
{
public:
	SecurityCamera();
	~SecurityCamera();

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

	void setYaw(float arg);
	void setPitch(float arg);
	void setRoll(float arg);

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
	Window win;
	Window *window = &win;
	float Yaw, Pitch, Roll;
};

#endif

