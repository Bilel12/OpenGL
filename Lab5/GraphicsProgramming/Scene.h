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
#include <conio.h>
// Further includes should go here:
#include "SOIL.h"

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
	bool light0, light1;

	float specular;
	float rotation;
	float rotation2;
	float position_x;
	float position_y;
	float position_z;
	float speed;
	// light variables
	GLfloat highSpec[4];
	GLfloat no_mat[4];
	GLfloat mat_ambient[4];
	GLfloat mat_ambient_colour[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];

	GLfloat shininess[1];
	GLfloat no_shininess[1];
	GLfloat low_shininess[1];
	GLfloat high_shininess[1];

	GLfloat Light_Ambient[4];
	GLfloat Light_Ambient1[4];
	GLfloat Light_Diffuse[4];
	GLfloat Light_Position[4];
	GLfloat Light_Position1[4];
	GLfloat spot_Direction[4];
	GLfloat Light_Specular[4];

	// Set light
	GLfloat* setLightAmbient(float x, float y, float z, float w, GLfloat* lightAmbient);
	GLfloat* setLightDiffuse(float x, float y, float z, float w, GLfloat* lightDiffuse);
	GLfloat* setLightPosition(float x, float y, float z, float w, GLfloat* lightPosition);
	GLfloat* setSpotDirection(float x, float y, float z, float w, GLfloat* spotDirection);
	// Set light Specular
	GLfloat* setLightSpecular(float x, float y, float z, float w, GLfloat* lightSpecular);
	GLfloat* setHighSpec(float x, float y, float z, float w, GLfloat* highSpec);
	GLfloat* set_no_mat(float x, float y, float z, float w, GLfloat* no_mat);
	GLfloat* set_mat_ambient(float x, float y, float z, float w, GLfloat* mat_ambient);
	GLfloat* set_mat_ambient_colour(float x, float y, float z, float w, GLfloat* mat_ambient_colour);
	GLfloat* set_mat_diffuse(float x, float y, float z, float w, GLfloat* mat_diffuse);
	GLfloat* set_mat_specular(float x, float y, float z, float w, GLfloat* mat_specular);
	GLfloat* set_mat_emission(float x, float y, float z, float w, GLfloat* mat_emission);
	// Set variables
	GLfloat* set_shininess(float s, GLfloat* shininess);
	GLfloat* set_no_shininess(float s, GLfloat* no_shininess);
	GLfloat* set_low_shininess(float s, GLfloat* low_shininess);
	GLfloat* set_high_shininess(float s, GLfloat* high_shininess);
};



#endif