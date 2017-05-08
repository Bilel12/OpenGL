#include "LoadScene.h"

LoadScene::LoadScene()
{
	cout << "Load Scene constructor called!\n";
	//GameScene *game_scene = new GameScene(in);
}

LoadScene::~LoadScene()
{
	cout << "Load Scene destructor called!\n";
}

void LoadScene::render()
{

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();

	// Set the camera
	/*gluLookAt(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ(),
		camera->getLookAtX(), camera->getLookAtY(), camera->getLookAtZ(),
		camera->getUpX(), camera->getUpY(), camera->getUpZ());*/
	
	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Render geometry here -------------------------------------
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 2.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
	// Geometry rendering ends here -----------------------------
	
	//if (development) { renderTextOutput(); }
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void LoadScene::update(float dt)
{
	// Calculate FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

void LoadScene::resize(int w, int h)
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

void LoadScene::displayText(float x, float y, float r, float g, float b, const char * string)
{
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

	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);
	glEnable(GL_LIGHTING);
	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void LoadScene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	// sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	// displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}
