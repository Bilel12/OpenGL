#include "Scene.h"

Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_LIGHTING);								// Enable Lighting
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glEnable(GL_COLOR_MATERIAL);						// Without it all glColor3f() changes are ignored when lighting is enabled

	// Other OpenGL / render setting should be applied here.
	setLightAmbient(0, 0, 1, 1, Light_Ambient);
	setLightAmbient(0, 1, 1, 0, Light_Ambient1);
	setLightPosition(0, -1, 0, 1, Light_Position);
	setLightDiffuse(0, 1, 1, 1, Light_Diffuse);
	setLightPosition(0, 0, 1, 1, Light_Position1);
	setSpotDirection(0, -1, 0, 0, spot_Direction);

	// Initialise variables
	light0 = true; light1 = false;
	specular = 0.1f;
	rotation = 1;
	rotation2 = 1;
	light_x = 0;
	light_y = -1;
	light_z = 0;
	speed = 5;

	// Light 0
	
}

void Scene::update(float dt)
{
	// Handle user input
	//key = _getch();
	//switch (input->isKeyDown(key)) {
	//	case 'a' : specular -= 1; input->SetKeyDown(key); break;
	//	default: break;
	//}
	// increase specular
	if (input->isKeyDown('i') || input->isKeyDown('I')) {
		specular += 0.1;
	}
	// reduce specular
	if (input->isKeyDown('u') || input->isKeyDown('U')) {
		specular -= 0.1;
	}
	// move right
	if (input->isKeyDown('d') || input->isKeyDown('D')) {
		light_x += 1;
	}
	// move left
	if (input->isKeyDown('a') || input->isKeyDown('A')) {
		light_x -= 1;
	}
	// move up
	if (input->isKeyDown('w') || input->isKeyDown('w')) {
		light_y += 1;
	}
	// move down
	if (input->isKeyDown('s') || input->isKeyDown('S')) {
		light_y -= 1;
	}
	// move z towards
	if (input->isKeyDown('r') || input->isKeyDown('R')) {
		light_z += 1;
	}
	// move z inwards
	if (input->isKeyDown('f') || input->isKeyDown('F')) {
		light_z -= 1;
	}
	if (input->isKeyDown('l') || input->isKeyDown('L')) {
		light0 = !light0;
		light1 = !light1;
		input->SetKeyUp('l'); input->SetKeyUp('L');
	}


	// Update object and variables (camera, rotation, etc).
	rotation += speed * dt;
	rotation2 += (speed * 2) * dt;
	Light_Position[2] += speed * dt;

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
	glRotatef(20, 1, 0, 0); // Rotate by x-axis

	
	//glRotatef(rotation, 0.0f, 1.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_Direction);
	
	glEnable(GL_LIGHT0);
	
	// enable light1
	//if (light0)
		//glEnable(GL_LIGHT0);
//	else
		//glDisable(GL_LIGHT0);
	

	glPushMatrix();
		/*glBegin(GL_POINT);
			glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();*/
		//glRotatef(rotation, 0.0f, 1.0f, 0.0f);
		glTranslatef(2, 0, 0);
		glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient1);
		glLightfv(GL_LIGHT1, GL_POSITION, Light_Position1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.125);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
		gluSphere(gluNewQuadric(), 0.20, 20, 20);
		// enable light1
	//	if (light1)
			glEnable(GL_LIGHT1);
	//	else
		//	glDisable(GL_LIGHT1);
	glPopMatrix();

	setLightAmbient(0.4f, 0.4f, 0.4f, 1.0f, Light_Ambient);
	setLightDiffuse(1.0f, 1.0f, 1.0f, 1.0f, Light_Diffuse);
	setLightSpecular(specular, specular, specular, specular, Light_Specular);
	setLightPosition(light_x, light_y, light_z, 1, Light_Position);

	set_shininess(100.0, shininess);
	setHighSpec(1.0, 1.0, 1.0, 1.0, highSpec);

	set_no_mat(0.2, 0.2, 0.2, 0.2, no_mat);
	set_mat_ambient(0.7, 0.7, 0.7, 1.0, mat_ambient);
	set_mat_ambient_colour(0.8, 0.8, 0.2, 1.0, mat_ambient_colour);
	set_mat_diffuse(0.1, 0.5, 0.8, 1.0, mat_diffuse);
	set_mat_specular(3.0, 3.0, 3.0, 3.0, mat_specular);
	set_no_shininess(300.0, no_shininess);
	set_low_shininess(50, low_shininess);
	set_high_shininess(100, high_shininess);
	set_mat_emission(0.3, 0.2, 0.2, 0.0, mat_emission);

	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light_Specular);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.25);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.15);
	//glEnable(GL_LIGHT2);

	glMaterialfv(GL_FRONT, GL_SPECULAR, highSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	// Render geometry here -----------------------------------

	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(-2.0, -1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		gluSphere(gluNewQuadric(), 1, 4000, 4000);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(2.0, -1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		gluSphere(gluNewQuadric(), 1.0, 40, 40);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(0.0, 1.5, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		gluSphere(gluNewQuadric(), 0.5, 40, 40);
	glPopMatrix();

	// Geometry rendering ends here -----------------------------
	
	//glBegin(GL_TRIANGLES);
	//// front face
	//glColor3f(1.0f, 0.0f, 0.0f);	
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, 1.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);/////////////
	//// left face
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, -1.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 0.0f, -1.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 1.0f, -1.0f);/////////////
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);/////////////
	//// bottom face
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);/////////////
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, 0.0f);/////////////
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, -1.0f);/////////////
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glVertex3f(1.0f, 0.0f, -1.0f);/////////////
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, -1.0f);/////////////
	//glNormal3f(0.0f, -1.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);/////////////

	//glEnd();
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

GLfloat* Scene::setLightAmbient(float x, float y, float z, float w, GLfloat* lightAmbient) {
	lightAmbient[0] = x;
	lightAmbient[1] = y;
	lightAmbient[2] = z;
	lightAmbient[3] = w;

	return lightAmbient;
}

GLfloat* Scene::setLightDiffuse(float x, float y, float z, float w, GLfloat* lightDiffuse) {
	lightDiffuse[0] = x;
	lightDiffuse[1] = y;
	lightDiffuse[2] = z;
	lightDiffuse[3] = w;

	return lightDiffuse;
}

GLfloat* Scene::setLightPosition(float x, float y, float z, float w, GLfloat* lightPosition) {
	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;
	lightPosition[3] = w;

	return lightPosition;
}

GLfloat* Scene::setSpotDirection(float x, float y, float z, float w, GLfloat* spotDirection) {
	spotDirection[0] = x;
	spotDirection[1] = y;
	spotDirection[2] = z;
	spotDirection[3] = w;

	return spotDirection;
}

GLfloat* Scene::setLightSpecular(float x, float y, float z, float w, GLfloat* lightSpecular) {
	lightSpecular[0] = x;
	lightSpecular[1] = y;
	lightSpecular[2] = z;
	lightSpecular[3] = w;

	return lightSpecular;
}

GLfloat* Scene::set_no_mat(float x, float y, float z, float w, GLfloat* no_mat) {
	no_mat[0] = x;
	no_mat[1] = y;
	no_mat[2] = z;
	no_mat[3] = w;

	return no_mat;
}

GLfloat* Scene::set_mat_ambient(float x, float y, float z, float w, GLfloat* mat_ambient) {
	mat_ambient[0] = x;
	mat_ambient[1] = y;
	mat_ambient[2] = z;
	mat_ambient[3] = w;

	return mat_ambient;
}

GLfloat* Scene::set_mat_ambient_colour(float x, float y, float z, float w, GLfloat* mat_ambient_colour) {
	mat_ambient_colour[0] = x;
	mat_ambient_colour[1] = y;
	mat_ambient_colour[2] = z;
	mat_ambient_colour[3] = w;

	return mat_ambient_colour;
}

GLfloat* Scene::set_mat_diffuse(float x, float y, float z, float w, GLfloat* mat_diffuse) {
	mat_diffuse[0] = x;
	mat_diffuse[1] = y;
	mat_diffuse[2] = z;
	mat_diffuse[3] = w;

	return mat_diffuse;
}

GLfloat* Scene::set_mat_specular(float x, float y, float z, float w, GLfloat* mat_specular) {
	mat_specular[0] = x;
	mat_specular[1] = y;
	mat_specular[2] = z;
	mat_specular[3] = w;

	return mat_specular;
}

GLfloat* Scene::set_mat_emission(float x, float y, float z, float w, GLfloat* mat_emission) {
	mat_emission[0] = x;
	mat_emission[1] = y;
	mat_emission[2] = z;
	mat_emission[3] = w;

	return mat_emission;
}


GLfloat* Scene::setHighSpec(float x, float y, float z, float w, GLfloat* highSpec) {
	highSpec[0] = x;
	highSpec[1] = y;
	highSpec[2] = z;
	highSpec[3] = w;

	return highSpec;
}

GLfloat* Scene::set_shininess(float s, GLfloat* shininess) {
	shininess[0] = s;

	return shininess;
}
GLfloat* Scene::set_no_shininess(float s, GLfloat* no_shininess) {
	no_shininess[0] = s;

	return no_shininess;
}

GLfloat* Scene::set_low_shininess(float s, GLfloat* low_shininess) {
	low_shininess[0] = s;

	return low_shininess;
}

GLfloat* Scene::set_high_shininess(float s, GLfloat* high_shininess) {
	high_shininess[0] = s;

	return high_shininess;
}

