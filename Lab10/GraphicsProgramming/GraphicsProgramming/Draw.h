#ifndef _DRAW_H
#define _DRAW_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <vector>
// Remember atom beautify
class Draw {
public:
	//static void drawTorus(int numc, int numt);
	// Floor variables
	void drawFloor(float x, float y, float z);
	// Square varaibles
	void drawSquare(float x, float y, float z, GLuint *texture);
	// Circle functions
	void drawCircle(int edges, float x, float y, float z);
	void drawSphereTorus(int edges, float x, float y, float z, float rot_interval);
	void drawCylinder(float radius, float edges, float height, float x, float y, float z, GLuint *texture);
	void drawCylinderLowPoli(float radius, float edges, float height, float x, float y, float z, GLuint *disk_texture, GLuint *side_texture);
	void drawCylinderHighPoli(float radius, float edges, float height, float x, float y, float z, GLuint *disk_texture, GLuint *side_texture);
	// Cone functions
	void drawCone(float radius, float edges, float height, float x, float y, float z, GLuint *texture);
	// Disc functions
	void drawDisc(int edges, float radius, float x, float y, float z, GLuint *texture);
	// Flat Disc functions
	void drawFlatDisc(int edges, float radius, float x, float z, GLuint * texture);
	// Sphere functions
	void drawSphere(double radius, double latitude, double longitude, GLuint * texture);
	float calc_x0(float radius, float theta, float delta);
	float calc_y0(float radius, float theta, float delta);
	float calc_z0(float radius, float theta, float delta);

	float calc_x1(float radius, float theta, float delta, float delta_interval);
	float calc_y1(float radius, float theta, float delta, float delta_interval);
	float calc_z1(float radius, float theta, float delta, float delta_interval);

	float calc_x2(float radius, float theta, float delta, float delta_interval, float theta_interval);
	float calc_y2(float radius, float theta, float delta, float delta_interval);
	float calc_z2(float radius, float theta, float delta, float delta_interval, float theta_interval);

	float calc_x3(float radius, float theta, float delta, float theta_interval);
	float calc_y3(float radius, float theta, float delta, float theta_interval);
	float calc_z3(float radius, float theta, float delta, float theta_interval);

	float calc_n_x0(float radius, float theta, float delta);
	float calc_n_y0(float radius, float theta, float delta);
	float calc_n_z0(float radius, float theta, float delta);

	float calc_n_x1(float radius, float theta, float delta, float delta_interval);
	float calc_n_y1(float radius, float theta, float delta, float delta_interval);
	float calc_n_z1(float radius, float theta, float delta, float delta_interval);

	float calc_n_x2(float radius, float theta, float delta, float delta_interval, float theta_interval);
	float calc_n_y2(float radius, float theta, float delta, float delta_interval);
	float calc_n_z2(float radius, float theta, float delta, float delta_interval, float theta_interval);

	float calc_n_x3(float radius, float theta, float delta, float theta_interval);
	float calc_n_y3(float radius, float theta, float delta, float theta_interval);
	float calc_n_z3(float radius, float theta, float delta, float theta_interval);

	//void drawIcosahedron();
	//void normalize(float v[3]);
	//void normcrossprod(float v1[3], float v2[3], float out[3]);
};


#endif 
