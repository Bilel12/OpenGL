// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:


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

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	float rotation;
	float rotation2;
	float speed;

	GLfloat Light_Ambient[4];
	GLfloat Light_Ambient1[4];
	GLfloat Light_Diffuse[4];
	GLfloat Light_Position[4];
	GLfloat Light_Position1[4];
	GLfloat spot_Direction[4];

	// Populate Light_Ambient
	GLfloat* populateLightAmbient(float x, float y, float z, float w, GLfloat* lightAmbient);
	GLfloat* populateLightDiffuse(float x, float y, float z, float w, GLfloat* lightDiffuse);
	GLfloat* populateLightPosition(float x, float y, float z, float w, GLfloat* lightPosition);
	GLfloat* populateSpotDirection(float x, float y, float z, float w, GLfloat* spotDirection);
};



#endif