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
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// Other OpenGL / render setting should be applied here.

	// Initialise variables
	rotation = 1;
	rotation = 1;
	speed = 2;
}

void Scene::update(float dt)
{
	// Handle user input
	if (input->isKeyDown('6')) {
		rotation += 10.0;
	}
	if (input->isKeyDown('4')) {
		rotation -= 10.0;
	}

	// Update object and variables (camera, rotation, etc).
	rotation += speed * dt;
	rotation2 += (speed * 2) * dt;

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
	// Set up scene START
	// Translation
	glTranslatef(-1.0f, 0.0f, 0.0f);
	// Tilt the solar system slightly so it isn't on the eye plane
	glRotatef(20, 1, 0, 0); // Rotate by x-axis
	// Set up scene END

	glPushMatrix(); // SOLAR SYSTEM
	{ // OBJECT1 start. Remember where we are THE SUN
		// render the sun
		glColor3f(1.0f, 0.9f, 0.0f);
		gluSphere(gluNewQuadric(), 0.20, 20, 20);
		//////////////////////////////////////////////////////////////////// ORBIT1
		glPushMatrix(); 
		{ // OBJECT2 start. Move from THE SUN by 1
			// render PLANET1
			glRotatef(rotation, 0, 1, 0);
			glTranslatef(1, 0, 0);
			glScalef(0.1, 0.1, 0.1);
			gluSphere(gluNewQuadric(), 0.20, 20, 20);
		} glPopMatrix(); // OBJECT2 end. Move BACK to THE SUN
		/////////////////////////////////////////////////////////////////// ORBIT2
		glPushMatrix(); 
		{ // OBJECT3 start. REMEMBER WHERE WE ARE. Move from THE SUN by 1.5. Scale down by 0.3
			// draw PLANET2
			glRotatef(rotation, 0, 0, 1);
			glTranslatef(1.5, 0, 0);
			glScalef(0.3, 0.3, 0.3);
			glColor3f(0.1f, 0.9f, 1.0f);
			gluSphere(gluNewQuadric(), 0.20, 20, 20);
			glPushMatrix(); 
			{ // Object 4 start. REMEMBER WHERE WE ARE. Move from PLANET2 by 1.5. Futher scale down by 0.3
				// draw a MOON around PLANET2
				glRotatef(-rotation * 2.0, 0, 0, 1);
				glTranslatef(1.5, 0, 0);
				glScalef(0.3, 0.3, 0.3);
				glColor3f(0.1f, 0.9f, 1.0f);
				gluSphere(gluNewQuadric(), 0.20, 20, 20);
					glPushMatrix(); { // Object 5 start. REMEMBER WHERE WE ARE. Move from MOON by 1.5. Futher Scale down by 0.3
						// draw a MOON around the MOON
						glRotatef(-rotation * 2.0, 0, 0, 1);
						glTranslatef(1.5, 0, 0);
						glScalef(0.3, 0.3, 0.3);
						glColor3f(0.1f, 0.9f, 1.0f);
						gluSphere(gluNewQuadric(), 0.20, 20, 20);
					} glPopMatrix(); // OBJECT5 end
			} glPopMatrix(); // OBJECT4 end
		} glPopMatrix(); // OBJECT3 end	
	} glPopMatrix(); // OBJECT1 end
	// Reset colour
	glColor3f(1.0f, 1.0f, 1.0f);
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

void Scene::drawTriangle() {
	glBegin(GL_TRIANGLES);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
}
