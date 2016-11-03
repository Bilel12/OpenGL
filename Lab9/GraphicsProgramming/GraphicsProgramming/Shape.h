#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

class Shape {
public:
	void render1();
	void render3();
	void render_cube();
	void render_skybox();
	void render_disc();
};
#endif 
