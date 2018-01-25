#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_

// Include GLUT, openGL, input.
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include <gl/GLU.h>
#include <gl/GL.h>
#include "Input.h"
// concurrency libraries
#include <thread>
// Further includes should go here:
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "SOIL.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "SecurityCamera.h"
#include "TopDownCamera.h"
#include "Shape.h"
#include "Cube.h"
#include "Skybox.h"
#include "Model.h"
#include "Timing.h"
#include "Scene.h"
#include "GameScene.h"


class LoadScene : public Scene
{
public:
	LoadScene();
	~LoadScene();

	// Main render function
	void render();
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	Vector3 a;
	Vector3 b;

	Camera *camera;
protected:
	// For Window and frustum calculation.
	int width, height;
	// For FPS counter and mouse coordinate output.
	int frame, time, timebase;
	char fps[40];
	char mouseText[60];
	float fov, nearPlane, farPlane;
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, const char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
};

#endif

