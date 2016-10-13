#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"


class Camera
{
public:
	Camera();
	~Camera();

	void update();
	float getForwardX();
	float getForwardY();
	float getForwardZ();
	float getUpX();
	float getUpY();
	float getUpZ();
	float getYaw();
	float getPitch();
	float getRoll();

private:
	//Vector3* p_forward = &forward;
	Vector3 forward;
	Vector3 up;
	Vector3 side;
	float Yaw;
	float Pitch;
	float Roll;
};

#endif 

