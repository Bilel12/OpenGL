#ifndef _SHAPE_H
#define _SHAPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

class Shape
{
	public:
		void render1();
		void render3();
		void render_crate();
		void render_crate_blend();
		void render_skybox();

};
#endif 
