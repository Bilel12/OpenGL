#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Input.h"
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <vector>
// Remember atom beautify
class Shape {
public:
	void render1();
	void render3();
	void drawCube(GLuint * texture);
	void drawBlendCube(GLuint *texture);
	void drawSkybox();
	//static void drawTorus(int numc, int numt);
	void drawFloor(float x, float y, float z);
	void drawSquare(float x, float y, float z, GLuint *texture);
	void drawCircle(int edges, float x, float y, float z);
	void drawSphereTorus(int edges, float x, float y, float z, float rot_interval);
	void drawCylinder(float radius, float edges, float height, float x, float y, float z, GLuint *texture);
	void drawCylinderLowPoli(float radius, float edges, float height, float x, float y, float z, GLuint *disk_texture, GLuint *side_texture);
	void drawCylinderHighPoli(float radius, float edges, float height, float x, float y, float z, GLuint *disk_texture, GLuint *side_texture);
	void drawCone(float radius, float edges, float height, float x, float y, float z, GLuint *texture);
	void drawDisc(int edges, float radius, float x, float y, float z, GLuint *texture);
	void drawFlatDisc(int edges, float radius, float h, float k, GLuint *texture);
	// Sphere functions
	void buildSphere(double radius, double latitude, double longitude);
	void renderSphere(GLuint *texture);
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
private:
	// sphere variables
	std::vector<float> sphere_verts, sphere_norms, sphere_texcoords;
};

//void drawtriangle(float *v1, float *v2, float *v3)
//{
//	glBegin(GL_TRIANGLES);
//	glNormal3fv(v1); glVertex3fv(v1);
//	glNormal3fv(v2); glVertex3fv(v2);
//	glNormal3fv(v3); glVertex3fv(v3);
//	glEnd();
//}
//
//void subdivide(float *v1, float *v2, float *v3)
//{
//	GLfloat v12[3], v23[3], v31[3];
//	GLint i;
//
//	for (i = 0; i < 3; i++) {
//		v12[i] = v1[i] + v2[i];
//		v23[i] = v2[i] + v3[i];
//		v31[i] = v3[i] + v1[i];
//	}
//	normalize(v12);
//	normalize(v23);
//	normalize(v31);
//	drawtriangle(v1, v12, v31);
//	drawtriangle(v2, v23, v12);
//	drawtriangle(v3, v31, v23);
//	drawtriangle(v12, v23, v31);
//}

#endif
