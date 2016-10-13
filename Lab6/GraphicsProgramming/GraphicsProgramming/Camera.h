#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"


class Camera
{
public:
	Camera();
	~Camera();

	void update();
	void moveForward(float dt);
	void moveBackwards(float dt);
	void moveUp(float dt);
	void moveDown(float dt);

	void addYaw(float dt);
	void subtractYaw(float dt);
	void addPitch(float dt);
	void subtractPutch(float dt);
	void addRoll(float dt);
	void subtractroll(float dt);

	float getPositionX();
	float getPositionY();
	float getPositionZ();

	float getForwardX();
	float getForwardY();
	float getForwardZ();

	float getLookAtX();
	float getLookAtY();
	float getLookAtZ();

	float getUpX();
	float getUpY();
	float getUpZ();

	float getYaw();
	float getPitch();
	float getRoll();

private:
	//Vector3* p_forward = &forward;
	Vector3 position;
	Vector3 lookAt;
	Vector3 forward;
	Vector3 up;
	Vector3 side;
	float Yaw;
	float Pitch;
	float Roll;
};

#endif 

