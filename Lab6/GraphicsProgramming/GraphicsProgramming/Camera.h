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

	void getMousePositionX(int width, int mouseX, int speed);
	void getMousePositionY(int height, int mouseY, int speed);

private:
	//Vector3* p_forward = &forward;
	Vector3 position, lookAt, forward, up, side;
	float Yaw, Pitch, Roll;
};

#endif 

