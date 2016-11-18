#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#define M_PI           3.14159265358979323846  /* pi */

using std::cout;
using std::endl;

class Shape
{
public:
	Shape();
	~Shape();
	
	void drawSphere(double radius, double latitude, double longitude);

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

	void buildSphere(double radius, double latitude, double longitude);
	std::vector<double> vertices_sphere, normals_sphere, texcoords_sphere;
};

#endif

