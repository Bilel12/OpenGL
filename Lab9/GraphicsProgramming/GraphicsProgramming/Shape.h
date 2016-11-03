#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

class Shape {
public:
	void render1();
	void render3();
	void render_cube();
	void render_skybox();
	void render_disc();
	static void drawTorus(int numc, int numt);
	void drawCircle(int edges);
	void drawIcosahedron();
	void drawDisc();
	void normalize(float v[3]);
	void normcrossprod(float v1[3], float v2[3], float out[3]);
};
#endif 
