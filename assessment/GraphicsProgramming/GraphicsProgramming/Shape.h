#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <vector>
#include "Vector3.h"
// Remember atom beautify
class Shape {
public:
	Shape();
	~Shape();
	void render1();
	void render3();
	void renderCube(GLuint * texture);
	void renderBlendCube(GLuint *texture);
	void renderSkybox(GLuint *texture);
	//static void drawTorus(int numc, int numt);
	// Floor variables
	void buildFloor(float sca_x, float sca_y, float sca_z, 
					float pos_x, float pos_y, float pos_z, 
					float angle, float rot_x, float rot_y, float rot_z);
	void renderFloor(float R, float G, float B, float A);
	// Circle functions
	void buildCircle(float edges, 
					 float sca_x, float sca_y, float sca_z, 
					 float pos_x, float pos_y, float pos_z, 
					 float angle, float rot_x, float rot_y, float rot_z);
	void renderCircle();
	// Cone functions
	void buildCone(	float radius, float edges, float height, 
					float sca_x, float sca_y, float sca_z,
					float pos_x, float pos_y, float pos_z,
					float angle, float rot_x, float rot_y, float rot_z);
	void renderCone(GLuint *texture);
	// Disc functions
	void buildDisc(float edges, float radius, 
				   float sca_x, float sca_y, float sca_z, 
				   float pos_x, float pos_y, float pos_z, 
				   float angle, float rot_x, float rot_y, float rot_z);
	void renderDisc(GLuint *texture);
	// Cylinder functions and variables
	void buildCylinder(	float radius, float edges, float height, 
						float sca_x, float sca_y, float sca_z,
						float pos_x, float pos_y, float pos_z,
						float angle, float rot_x, float rot_y, float rot_z);
	void renderCylinder(GLuint *disk_texture);
	// Sphere functions
	void buildSphere(float radius, float latitude, float longitude,
					 float sca_x, float sca_y, float sca_z, 
					 float pos_x, float pos_y, float pos_z, 
					 float angle, float rot_x, float rot_y, float rot_z);
	void renderSphere(GLuint *texture);
	float sphere_x0(float radius, float theta, float delta);
	float sphere_y0(float radius, float theta, float delta);
	float sphere_z0(float radius, float theta, float delta);

	float sphere_x1(float radius, float theta, float delta, float delta_interval);
	float sphere_y1(float radius, float theta, float delta, float delta_interval);
	float sphere_z1(float radius, float theta, float delta, float delta_interval);

	float sphere_x2(float radius, float theta, float delta, float delta_interval, float theta_interval);
	float sphere_y2(float radius, float theta, float delta, float delta_interval);
	float sphere_z2(float radius, float theta, float delta, float delta_interval, float theta_interval);

	float sphere_x3(float radius, float theta, float delta, float theta_interval);
	float sphere_y3(float radius, float theta, float delta, float theta_interval);
	float sphere_z3(float radius, float theta, float delta, float theta_interval);

	float sphere_n_x0(float radius, float theta, float delta);
	float sphere_n_y0(float radius, float theta, float delta);
	float sphere_n_z0(float radius, float theta, float delta);

	float sphere_n_x1(float radius, float theta, float delta, float delta_interval);
	float sphere_n_y1(float radius, float theta, float delta, float delta_interval);
	float sphere_n_z1(float radius, float theta, float delta, float delta_interval);

	float sphere_n_x2(float radius, float theta, float delta, float delta_interval, float theta_interval);
	float sphere_n_y2(float radius, float theta, float delta, float delta_interval);
	float sphere_n_z2(float radius, float theta, float delta, float delta_interval, float theta_interval);

	float sphere_n_x3(float radius, float theta, float delta, float theta_interval);
	float sphere_n_y3(float radius, float theta, float delta, float theta_interval);
	float sphere_n_z3(float radius, float theta, float delta, float theta_interval);

	float rotate(float arg);
	void render(GLuint *texture);
	Vector3 translate, rotation, scale;
	//void drawIcosahedron();
	//void normalize(float v[3]);
	//void normcrossprod(float v1[3], float v2[3], float out[3]);
	// Material functions
	void set_ambient(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	void set_diffuse(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	void set_specular(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	void set_emission(GLfloat R, GLfloat G, GLfloat B, GLfloat A);

	void set_ambient(GLfloat *ambient);
	void set_diffuse(GLfloat *diffuse);
	void set_specular(GLfloat *specular);
	void set_emission(GLfloat *emission);

	void set_shininess(GLfloat *arg);
	void set_shininess(GLfloat arg);

private:
	std::vector<float> verts, norms, texcoords, colors;
	//GLfloat ambient[4];
	GLfloat ambient[4] = { static_cast<GLfloat>(0.2), static_cast<GLfloat>(0.2), static_cast<GLfloat>(0.2), static_cast<GLfloat>(1.0) };
	GLfloat diffuse[4] = { static_cast<GLfloat>(0.8), static_cast<GLfloat>(0.8), static_cast<GLfloat>(0.8), static_cast<GLfloat>(1.0) };
	GLfloat specular[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat emission[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess[1] = { 0.0 };

	//GLfloat ambient_def[4];
	GLfloat ambient_def[4] = { static_cast<GLfloat>(0.2), static_cast<GLfloat>(0.2), static_cast<GLfloat>(0.2), static_cast<GLfloat>(1.0) };
	GLfloat diffuse_def[4] = { static_cast<GLfloat>(0.8), static_cast<GLfloat>(0.8), static_cast<GLfloat>(0.8), static_cast<GLfloat>(1.0) };
	GLfloat specular_def[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat emission_def[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess_def[1] = { 0.0 };

	float rot_angle;
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
