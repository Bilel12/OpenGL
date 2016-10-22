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

	// loading textures into vector
	loadTextures();
	// Initialise variables
	triangle = &textures[2];
	checked = &textures[3];
	grass = &textures[4];
	glass = &textures[5];
	xrot = 0;	// Rotate On The X Axis
	yrot = 0;	// Rotate On The Y Axis
	zrot = 0;	// Rotate On The Z Axis
	position_x = 0, position_y = 0, position_z = 0;
	
	blend = false; // blending on/off?
}

void Scene::loadTextures() {
	myTexture = SOIL_load_OGL_texture( // 0
		"gfx/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 1
		"gfx/tileBrown_02.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 2
		"gfx/cratearrow.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 3
		"gfx/checked.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 4
		"gfx/grass1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 5
		"gfx/glass.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	//for (std::array<GLuint, 5>::iterator it = textures.begin(); it != textures.end() ; ++it) {
	for (int i : textures) {
		if (i == NULL) {
			MessageBox(NULL, "Texture failed to load", "help", MB_OK);
		}
	}
}

void Scene::update(float dt)
{
	// Handle user input
	// Blending
	if (input->isKeyDown('b') || input->isKeyDown('B')) { // is B pressed and bp FALSE?
		blend = !blend; // toggle blend (true/false)
		if (blend) {
			glEnable(GL_BLEND); // Turn blending on
			glDisable(GL_DEPTH_TEST); // Turn depth testing off
		} else {
			glDisable(GL_BLEND); // Turn blending off
			glEnable(GL_DEPTH_TEST); // Turn depth testing on
		}
		input->SetKeyUp('b');
	}
	// move camera forward
	if (input->isKeyDown('w') || input->isKeyDown('w')) {
		camera.moveForward(dt);
	}
	// move camera backwards
	if (input->isKeyDown('s') || input->isKeyDown('S')) {
		camera.moveBackwards(dt);
	}
	// move camera to the left
	if (input->isKeyDown('a') || input->isKeyDown('A')) {
		camera.moveSideLeft(dt);
	}
	// move camera to the right
	if (input->isKeyDown('d') || input->isKeyDown('D')) {
		camera.moveSideRight(dt);
	}
	// move camera down
	if (input->isKeyDown(GLUT_KEY_UP) || input->isKeyDown('r') || input->isKeyDown('R')) {
		camera.moveUp(dt);
	}
	// move camera down
	if (input->isKeyDown(GLUT_KEY_DOWN) || input->isKeyDown('f') || input->isKeyDown('F')) {
		camera.moveDown(dt);
	}
	// camera's Yaw mouse controll
	camera.getMousePositionX(width, input->getMouseX(), 2);
	// camera's Pitch mouse controll
	camera.getMousePositionY(height, input->getMouseY(), 2);
	// Force mouse to return to the centre of the window
	glutWarpPointer(width / 2, height / 2);

	// Update object and variables (camera, rotation, etc).
	p_camera->update();
	float mousePositionX(int width);
	float mousePositionY(int height);

	//xrot += 0.7;	// Rotate On The X Axis
	//yrot += 0.7;	// Rotate On The Y Axis
	//zrot += 0.7;	// Rotate On The Z Axis
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
	gluLookAt(camera.getPositionX(), camera.getPositionY(), camera.getPositionZ(), 
	          camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(),
			  camera.getUpX(), camera.getUpY(), camera.getUpZ()
	         );

	// Render geometry here -------------------------------------

	glPushMatrix();
		glRotatef(position_x, 1.0f, 0.0f, 0.0f);                     // Rotate On The X Axis
		glRotatef(position_y, 0.0f, 1.0f, 0.0f);                     // Rotate On The Y Axis
		glRotatef(position_z, 0.0f, 0.0f, 1.0f);                     // Rotate On The Z Axis

		if (blend) {
			glDisable(GL_BLEND); // Turn blending off
			glEnable(GL_DEPTH_TEST); // Turn depth testing on
		}
		glBindTexture(GL_TEXTURE_2D, *checked); {

			glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 0);
			glVertex3f(-5, 5, 0);

			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 1);
			glVertex3f(-5, -5, 0);

			glNormal3f(0, 0, 1);
			glTexCoord2f(1, 1);
			glVertex3f(5, -5, 0);

			glNormal3f(0, 0, 1);
			glTexCoord2f(1, 0);
			glVertex3f(5, 5, 0);
			glEnd();
		}
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(position_x, 1.0f, 0.0f, 0.0f);                     // Rotate On The X Axis
		glRotatef(position_y, 0.0f, 1.0f, 0.0f);                     // Rotate On The Y Axis
		glRotatef(position_z, 0.0f, 0.0f, 1.0f);                     // Rotate On The Z Axis
		if (blend) {
			glEnable(GL_BLEND); // Turn blending on
			glDisable(GL_DEPTH_TEST); // Turn depth testing off
		}
		glBindTexture(GL_TEXTURE_2D, *glass); {
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Full Brightness, 50% Alpha
			glBlendFunc(GL_SRC_ALPHA, GL_ONE); // Blending Function For Translucency Based On Source Alpha Value
			/////////////////////////////
			glBegin(GL_TRIANGLES); // front face
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, 1);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, 1);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, 1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, 1);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, 1);

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, 1);
			glEnd();
			/////////////////////////////
			glBegin(GL_TRIANGLES); // right side face
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(1, -1, 1);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, -1);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, 1, 1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, -1);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, -1);

			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, 1, 1);
			glEnd();
			///////////////////////////////////
			glBegin(GL_TRIANGLES); // left side face
			glColor3f(0, 0, 1);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, -1, -1);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-1, 1, -1);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, 1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, 1);

			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, 1);
			
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, -1, -1);
			glEnd();
			//////////////////////////////
			glBegin(GL_TRIANGLES); // bottom face
			glColor3f(1, 1, 1);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, -1, -1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-1, -1, 1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, -1, 1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, -1, 1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(1, -1, -1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, -1, -1);
			glEnd();
			///////////////////////////////
			glBegin(GL_TRIANGLES); // back face
			glColor3f(0, 1, 0); // green
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, -1);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1, -1, -1);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, -1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1, 1, -1);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0, 0);
			glVertex3f(-1, 1, -1);

			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0, 1);
			glVertex3f(-1, -1, -1);
			glEnd();
			///////////////////////
			glBegin(GL_TRIANGLES); // top face
			glColor3f(0.0, 1.0, 0.0); // green
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, 1, 1);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(1, 1, -1);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, 1, -1);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(-1, 1, -1);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(-1, 1, 1);

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(1, 1, 1);
			glEnd();
		}
	glPopMatrix();

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
