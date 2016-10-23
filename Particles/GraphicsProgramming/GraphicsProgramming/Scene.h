// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

#define	MAX_PARTICLES	1000		// Number Of Particles To Create
// Include GLUT, openGL, input.
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include <gl/GLU.h>
#include <gl/GL.h>
//#include <GL/glew.h>
//#include <GL/glut.h>
#include "Input.h"
#include <stdio.h>
#include <vector>
// Further includes should go here:
#include "SOIL.h"
#include "Camera.h"

class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void loadTextures();

	// For Window and frustum calculation.
	int width, height;
	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];
	float fov, nearPlane, farPlane;
	HDC hDC = NULL;
	// For access to user input.
	Input* input;
	// For camera access 
	Camera camera;
	Camera *p_camera = &camera;
	// For loading textures
	std::vector<GLuint> textures;
	GLuint myTexture;
	GLuint *triangle;
	GLuint *checked;
	GLuint *grass;
	GLuint *glass;
	// Rotation variables
	float position_x, position_y, position_z;
	float xrot;	// Rotate On The X Axis
	float yrot;	// Rotate On The Y Axis
	float zrot;	// Rotate On The Z Axis
	// Booleans
	bool blend; // toggle bledning effect
	// Particles
	bool	rainbow = true;				// Rainbow Mode?
	bool	sp;							// Spacebar Pressed?
	bool	rp;							// Enter Key Pressed?

	float	slowdown = 2.0f;				// Slow Down Particles
	float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
	float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
	float	zoom = -40.0f;				// Used To Zoom Out

	GLuint	loop;						// Misc Loop Variable
	GLuint	col;						// Current Color Selection
	GLuint	delay;						// Rainbow Effect Delay
	GLuint	*particle_texture;					// Storage For Our Particle Texture

	typedef struct						// Create A Structure For Particle
	{
		bool	active;					// Active (Yes/No)
		float	life;					// Particle Life
		float	fade;					// Fade Speed
		float	r;						// Red Value
		float	g;						// Green Value
		float	b;						// Blue Value
		float	x;						// X Position
		float	y;						// Y Position
		float	z;						// Z Position
		float	xi;						// X Direction
		float	yi;						// Y Direction
		float	zi;						// Z Direction
		float	xg;						// X Gravity
		float	yg;						// Y Gravity
		float	zg;						// Z Gravity
	}
	particles;							// Particles Structure

	particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)

	
};

#endif