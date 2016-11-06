#ifndef _SECURITYCAMERA_H
#define _SECURITYCAMERA_H

#include "glut.h"
#include "Input.h"
#include "Camera.h"

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

	virtual void addYaw(float dt, float value);
	virtual void subtractYaw(float dt, float value);
	virtual void addPitch(float dt, float value);
	virtual void subtractPitch(float dt, float value);
	virtual void addRoll(float dt, float value);
	virtual void subtractRoll(float dt, float value);

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

	virtual float getSideX();
	virtual float getSideY();
	virtual float getSideZ();

	virtual float getYaw();
	virtual float getPitch();
	virtual float getRoll();

	virtual void setYaw(float arg);
	virtual void setPitch(float arg);
	virtual void setRoll(float arg);

	virtual void updateYaw(int width, int mouseX, int speed);
	virtual void updatePitch(int height, int mouseY, int speed);

	virtual void userControll(float dt, int width, int height, Input *input);
	virtual void cameraControll(float dt, int width, int height);
	float mix(float x, float y, float a) {
		return x*(1 - a) + y*a;
	}
private:
	Vector3 position;
	Vector3 lookAt;
	Vector3 forward;
	Vector3 up;
	Vector3 side;
	float Yaw, Pitch, Roll;
	float clamp_value, camera_speed;
	float leftClamp, rightClamp;
	bool lerpRight;
	bool stop_camera;
};

#endif

