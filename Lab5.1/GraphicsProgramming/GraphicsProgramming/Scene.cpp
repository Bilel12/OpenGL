#include "Scene.h"

Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	// Other OpenGL / render setting should be applied here.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //For a textured object we can control how the final RGB for the rendered pixel is set (combination of texture and geometry colours)
	glEnable(GL_TEXTURE_2D);

	// Initialise variables
	myTexture = SOIL_load_OGL_texture (
		"gfx/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	BrownTexture = SOIL_load_OGL_texture(
		"gfx/tileBrown_02.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	TriangleTexture = SOIL_load_OGL_texture(
		"gfx/triangle.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if (BrownTexture == NULL || TriangleTexture == NULL || myTexture == NULL) {
		MessageBox(NULL, "Texture failed to load", "help", MB_OK);
	}
}

void Scene::update(float dt)
{
	// Handle user input
	// Update object and variables (camera, rotation, etc).

	// Calculate FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Render geometry here -------------------------------------
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//glBindTexture(GL_TEXTURE_2D, myTexture);	//tells opengl which texture to use
	//glBegin(GL_QUADS);	//Begin drawing state
	////glColor3f(0.8, 0, 0);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-1.0f, 1.0f, 0.0f);

	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glTexCoord2f(0.0f, 3.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f);

	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glTexCoord2f(3.0f, 3.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f);

	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glTexCoord2f(3.0f, 0.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);
	//glEnd();		//end drawing

	//glBindTexture(GL_TEXTURE_2D, fuckOffFromMyTexture);	//tells opengl which texture to use
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glBegin(GL_QUADS);	//Begin drawing state
	//	//glColor3f(0.8, 0, 0);
	//	glNormal3f(0.0f, 0.0f, 1.0f);
	//	glTexCoord2f(0.0f, 0.0f);
	//	glVertex3f(-1.0f, 1.0f, 0.0f);

	//	glNormal3f(0.0f, 0.0f, 1.0f);
	//	glTexCoord2f(0.0f, 1.0f);
	//	glVertex3f(-1.0f, -1.0f, 0.0f);

	//	glNormal3f(0.0f, 0.0f, 1.0f);
	//	glTexCoord2f(1.0f, 1.0f);
	//	glVertex3f(1.0f, -1.0f, 0.0f);

	//	glNormal3f(0.0f, 0.0f, 1.0f);
	//	glTexCoord2f(1.0f, 0.0f);
	//	glVertex3f(1.0f, 1.0f, 0.0f);
	//glEnd();		//end drawing

	glBindTexture(GL_TEXTURE_2D, TriangleTexture); {
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, 0);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1, -1, 0);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(1, 1, 0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(1, 1, 0);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1, 1, 0);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1, -1, 0);
		glEnd();
	}

	/*glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);*/

	// Geometry rendering ends here -----------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
