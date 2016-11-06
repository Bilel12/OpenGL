#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
// Remember atom beautify
class Shape {
public:
	void render1();
	void render3();
	void drawCube();
	void drawSkybox();
	static void drawTorus(int numc, int numt);
	void drawCircle(int edges);
	void drawCylinder(float radius, float edges, float stacks, float h, float k);
	void drawIcosahedron();
	void drawDisc(int edges, float radius, float h, float k);
	void drawFlatDisc(int edges, float radius, float h, float k);
	void drawSphere(float radius, int lats, int longs, float h, float k);
	void normalize(float v[3]);
	void normcrossprod(float v1[3], float v2[3], float out[3]);
	//float* moveCube(float x, float y, float z, float* cube_verts);
};
#endif
