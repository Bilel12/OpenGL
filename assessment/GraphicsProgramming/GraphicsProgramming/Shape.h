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
	Vector3 translate, rotation, scale;
	//void drawIcosahedron();
	//void normalize(float v[3]);
	//void normcrossprod(float v1[3], float v2[3], float out[3]);

	// Material varaibles
	GLfloat no_mat[4];
	GLfloat mat_ambient[4];
	GLfloat mat_ambient_colour[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];
	GLfloat high_spec[4];

	GLfloat shininess[1];
	GLfloat no_shininess[1];
	GLfloat low_shininess[1];
	GLfloat high_shininess[1];
	// Default values
	GLfloat no_mat_def[4];
	GLfloat mat_ambient_def[4];
	GLfloat mat_ambient_colour_def[4];
	GLfloat mat_diffuse_def[4];
	GLfloat mat_specular_def[4];
	GLfloat mat_emission_def[4];
	GLfloat high_spec_def[4];

	GLfloat shininess_def[1];
	GLfloat no_shininess_def[1];
	GLfloat low_shininess_def[1];
	GLfloat high_shininess_def[1];
	// Material functions
	// Set material arrays
	GLfloat* set_no_mat(float x, float y, float z, float w, GLfloat* no_mat);
	GLfloat* set_mat_ambient(float x, float y, float z, float w, GLfloat* mat_ambient);
	GLfloat* set_mat_ambient_colour(float x, float y, float z, float w, GLfloat* mat_ambient_colour);
	GLfloat* set_mat_diffuse(float x, float y, float z, float w, GLfloat* mat_diffuse);
	GLfloat* set_mat_specular(float x, float y, float z, float w, GLfloat* mat_specular);
	GLfloat* set_mat_emission(float x, float y, float z, float w, GLfloat* mat_emission);
	GLfloat* set_high_spec(float x, float y, float z, float w, GLfloat* high_spec);
	// Set material variables
	GLfloat* set_shininess(float s, GLfloat* shininess);
	GLfloat* set_no_shininess(float s, GLfloat* no_shininess);
	GLfloat* set_low_shininess(float s, GLfloat* low_shininess);
	GLfloat* set_high_shininess(float s, GLfloat* high_shininess);
private:
	std::vector<float> verts, norms, texcoords, colors;
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
