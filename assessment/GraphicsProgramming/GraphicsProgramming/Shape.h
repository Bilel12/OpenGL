#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <vector>
#include "Vector3.h"
#include "Vector4.h"

class Shape {
public:
	Shape();
	~Shape();

	void render();										// Rendering shapes using GL_TRIANGLES

	void render(GLenum primitive);						// render shape with passed: primitve

	void render(GLenum primitive,						// render shape with passed: primitve
				GLuint* texture);						// texture

	void render(GLenum primitive,						// render shape with passed: primitve
				float R, float G, float B, float A);	// colour

	void render(GLenum primitive,						// render shape with passed: primitve
				float R, float G, float B, float A,		// colour
				GLuint* texture);						// texture

	void render(GLenum primitive,						// render shape with passed: primitve
				Shape shape,							// shape
				float R, float G, float B, float A,		// colour
				GLuint* texture);						// texture

	void render(GLenum primitive,						// render shape with passed primitve 
				float R, float G, float B, float A,		// colour
				std::vector<float> verts,				// vertices
				std::vector<float> norms,				// normals
				std::vector<float> texcoords,			// texture coordinates
				GLuint* texture);						// texture
	
	void renderBlend(GLenum primitive,					// render shape with passed primitve 
					 float R, float G, float B, float A,// colour
					 std::vector<float> verts, 			// vertices
					 std::vector<float> norms, 			// normals
					 std::vector<float> texcoords, 		// texture coordinates
					 GLuint* texture);					// texture

	void renderColor(GLenum primitive);					// render shape using colour array with passed: primitve

	void renderColor(GLenum primitive,					// render shape using colour array with passed: primitve
					 GLuint* texture);					// texture

	void render2D();

	void renderSolarSystem(GLenum primitive,					// render shape with passed primitve 
						   float R, float G, float B, float A,	// colour
						   std::vector<float> verts,			// vertices
						   std::vector<float> norms,			// normals
						   std::vector<float> texcoords,		// texture coordinates
						   GLuint* texture);					// texture

	// Quads building functions
	void buildQuad(GLenum primitive,
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation zfloat rot_z);
		Vector4 rgba,
		std::vector<float> verts,
		std::vector<float> texcoords,
		GLuint *texture);
	void buildQuad(GLenum primitive,
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,
		Vector4 rgba,
		GLuint *texture);
	// Circle build function
	void Shape::buildCircle(GLenum primitive,
		float edges,											// number of circle's edges
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation z
		Vector4 rgba,
		GLuint *texture);
	// Cone build function
	void buildCone(GLenum primitive,
		float radius, float edges, float height,				// radius, edges, height
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation z
		Vector4 rgba,
		GLuint *texture);
	// Disc build function
	void buildDisc(GLenum primitive,
		float edges, float radius,								// edges, radius
		Vector3 translate,										// scale x, scale y, scale z,
		Vector3 scale,											// translate x, translate y, translate z,
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation z
		Vector4 rgba,
		GLuint *texture);
	// Torus building funtion
	void buildTorus(GLenum primitive,
		float r, float R, float tube_edges, float torus_edges,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, tube edges, torus edges
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation z
		Vector4 rgba,
		GLuint *texture);
	// Cylinder build function
	void buildCylinder(GLenum primitive,
		float radius, float edges, float height,				// cylinder radius, number of edges and height
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation z
		Vector4 rgba,
		GLuint *texture);
	// Sphere build functions
	void buildSphere(GLenum primitive,
		float radius, float longitude, float latitude,			// sphere radius, number of latitudes, number of longitudes
		Vector3 translate,										// scale x, scale y, scale z
		Vector3 scale,											// translate x, translate y, translate z
		Vector4 rotation,										// rotation angle, rotation x, rotation y, rotation z
		Vector4 rgba,
		GLuint *texture);
	// 0 - left bottom
	float sphere_x0(	float radius, float theta, float delta);
	float sphere_y0(	float radius, float theta, float delta);
	float sphere_z0(	float radius, float theta, float delta);
	// 1 - right bottom
	float sphere_x1(	float radius, float theta, float delta, float delta_interval);
	float sphere_y1(	float radius, float theta, float delta, float delta_interval);
	float sphere_z1(	float radius, float theta, float delta, float delta_interval);
	// 2 - right top
	float sphere_x2(	float radius, float theta, float delta, float delta_interval, float theta_interval);
	float sphere_y2(	float radius, float theta, float delta, float delta_interval);
	float sphere_z2(	float radius, float theta, float delta, float delta_interval, float theta_interval);
	// 3 - left top
	float sphere_x3(	float radius, float theta, float delta, float theta_interval);
	float sphere_y3(	float radius, float theta, float delta, float theta_interval);
	float sphere_z3(	float radius, float theta, float delta, float theta_interval);
	// 0 - left bottom normal
	float sphere_n_x0(	float radius, float theta, float delta);
	float sphere_n_y0(	float radius, float theta, float delta);
	float sphere_n_z0(	float radius, float theta, float delta);
	// 1 - right bottom normal
	float sphere_n_x1(	float radius, float theta, float delta, float delta_interval);
	float sphere_n_y1(	float radius, float theta, float delta, float delta_interval);
	float sphere_n_z1(	float radius, float theta, float delta, float delta_interval);
	// 2 - right top normal
	float sphere_n_x2(	float radius, float theta, float delta, float delta_interval, float theta_interval);
	float sphere_n_y2(	float radius, float theta, float delta, float delta_interval);
	float sphere_n_z2(	float radius, float theta, float delta, float delta_interval, float theta_interval);
	// 3 - left top normal
	float sphere_n_x3(	float radius, float theta, float delta, float theta_interval);
	float sphere_n_y3(	float radius, float theta, float delta, float theta_interval);
	float sphere_n_z3(	float radius, float theta, float delta, float theta_interval);
	// Butterfly
	void createButterfly(GLenum primitive,
						 int N,
						 Vector3 translate,
						 Vector3 scale,
						 Vector4 rotation,
						 Vector4 rgba);
	// Ico
	void buildIco(GLenum primitive,
		Vector3 a, Vector3 b, float radius,
		Vector3 translate,
		Vector3 scale,
		Vector4 rotation,
		Vector4 rgba,
		GLuint *texture);
	float distance(		Vector3 a, Vector3 b);
	Vector3 normalize(	Vector3 a, Vector3 b, float length);

	// Vector3 variables to be used in render functions with shapes for 
	Vector3 _scale;
	Vector3 _translate;
	Vector4 _rotation;
	Vector4 _rgba;
	// Material setting functions
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
	// Getting verts, norms and texcoords vectors functions
	std::vector<GLfloat>* get_verts();
	std::vector<GLfloat>* get_norms();
	std::vector<GLfloat>* get_texcoords();
	// Get rot_angle variable function
	void rotate(float arg);
	// Primitive functions
	void set_primitive(GLenum primitive);
	GLenum get_primitive();
	GLuint *_texture;
private:
	// Variable to hold primitive to be used to render shape
	GLenum _primitive;
	// vectors for building shapes to storing:
	std::vector<GLfloat> _verts;			// verticies
	std::vector<GLfloat> _norms;			// normals
	std::vector<GLfloat> _texcoords;		// texture coordinates
	std::vector<GLfloat> _colors;		// colours
	// vectors for setting up materials':
	std::vector<GLfloat> ambient;		// ambient
	std::vector<GLfloat> diffuse;		// diffuse
	std::vector<GLfloat> specular;		// specular
	std::vector<GLfloat> emission;		// emission
	std::vector<GLfloat> shininess;		//shininess
	// vectors for restoring default values of:
	std::vector<GLfloat> ambient_def;	// ambient
	std::vector<GLfloat> diffuse_def;	// diffuse
	std::vector<GLfloat> specular_def;	// specular
	std::vector<GLfloat> emission_def;	// emission
	std::vector<GLfloat> shininess_def;	//shininess
};

#endif
