#include "Scene.h"

Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	// Camera
	camera = &freeCamera;
	//OpenGL settings
	frame = 0; timebase = 0;
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glShadeModel(GL_FLAT);
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear Stencil Buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	// Other OpenGL / render setting should be applied here.
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //For a textured object we can control how the final RGB for the rendered pixel is set (combination of texture and geometry colours)
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);					// Set The Blending Function For Translucency

	loadTextures();// loading textures into vector
	assignTextures();// assign textures to pointers
	loadModels();// load 3D models from files
	loadLists();// load lists
	// Initialise variables
	xrot = 0.0;	// Rotate On The X Axis
	yrot = 0.0;	// Rotate On The Y Axis
	zrot = 0.0;	// Rotate On The Z Axis
	angle = 0.0;
	position_x = 0, position_y = 0, position_z = 0;
	scale_x = 0, scale_y = 0, scale_z = 0;
	blend = false; // Blending on or off
	wireframe = false; // Wireframe on or off
	development = true;
	draw = false;
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

	myTexture = SOIL_load_OGL_texture( // 6
		"gfx/aTrans.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture); 

	myTexture = SOIL_load_OGL_texture( // 7
		"gfx/crateTrans.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture); 

	myTexture = SOIL_load_OGL_texture( // 8
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture); 

	myTexture = SOIL_load_OGL_texture( // 9
		"gfx/disk.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 10
		"gfx/barrel.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 11
		"gfx/globe.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 12
		"models/spaceship.jpg",
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

void Scene::assignTextures() {
	crate		= &textures[0]; 
	tileBrown	= &textures[1]; 
	crateArrow	= &textures[2]; 
	checked		= &textures[3]; 
	grass		= &textures[4]; 
	glass		= &textures[5]; 
	aTrans		= &textures[6]; 
	crateTrans	= &textures[7];
	skybox		= &textures[8]; 
	disk		= &textures[9];
	barrel		= &textures[10];
	globe		= &textures[11];
	spaceship	= &textures[12];
}

void Scene::loadModels() {
	model.load("models/spaceship.obj", "models/spaceship.jpg");
}

void Scene::loadLists() {
	Torus = glGenLists(1);
	glNewList(Torus, GL_COMPILE);
	shape.drawSphereTorus(100, 3.0, 0.0, 0.0, 0.1);
	glEndList();

	Disc = glGenLists(2);
	glNewList(Disc, GL_COMPILE);
	shape.drawDisc(100, 2, 3, 3, -10, disk);
	glEndList();

	Sphere = glGenLists(2);
	glNewList(Sphere, GL_COMPILE);
	shape.drawSphere(3.0, 200.0, 200.0, 0., 0., 0., globe);
	glEndList();

	LowPoliCylinder = glGenLists(3);
	glNewList(LowPoliCylinder, GL_COMPILE);
	shape.drawCylinderLowPoli(3., 6., 3., -5., 0., -1., disk, globe);
	glEndList();

	HighPoliCylinder = glGenLists(4);
	glNewList(HighPoliCylinder, GL_COMPILE);
	shape.drawCylinderHighPoli(3., 100., 3., 5., 0., -1., disk, globe);
	glEndList();
}

void Scene::renderLists() {
	//glCallList(Torus);
	glCallList(Sphere);
	glCallList(Disc);
	glCallList(LowPoliCylinder);
	glCallList(HighPoliCylinder);
	glFlush();
}

void Scene::renderShapes() {
	//shape.drawDisc(200.0, 2.0, -3.0, 3.0, -10.0, disk);
	//shape.drawCone(2.0, 100.0, 10.0, 5.0, 5.0, -10., disk);
	//shape.drawCylinder(2.0, 200.0, 3.0, 0.0, 5.0, -5.0, barrel);
	//shape.drawBlendCube(crateTrans);
	shape.drawSquare(0, .2, 0, NULL);
	//shape.drawSphereTorus(100, scale_x, scale_y, scale_z, 0.23); // frame rate starts droping at rot_interval < 0.13 on MAC < 0.23 on Uni PCs
	//shape.drawIcosahedron();
	//shape.drawCircle(100.0, 0.0, 0.0, 0.0);
	//shape.drawIcosahedron();
}

void Scene::update(float dt) {
	// Handle user input
	// Press 1 to switch to Free Camera
	if (input->isKeyDown('1')) {
		camera = &freeCamera;
		input->SetKeyUp('1');
	}
	// Press 2 to switch to Security Camera
	if (input->isKeyDown('2')) {
		camera = &securityCamera;
		input->SetKeyUp('2');
	}
	// Press 3 to switch to TopDown Camera
	if (input->isKeyDown('3')) {
		camera = &topDownCamera;
		input->SetKeyUp('3');
	}
	// Press B to toggle blending mode
	if (input->isKeyDown('b') || input->isKeyDown('B')) { // is B pressed and bp FALSE?
		blend = !blend; // toggle blend (true/false)
		input->SetKeyUp('b'); input->SetKeyUp('B');
	}
	// Press W and M at the same time to toggle wirefram mode
	if (input->isKeyDown('w') && input->isKeyDown('m') ||
		input->isKeyDown('W') && input->isKeyDown('M')) {
		wireframe = !wireframe; // toggle wireframe (true/false)
		input->SetKeyUp('w'); input->SetKeyUp('m');
		input->SetKeyUp('W'); input->SetKeyUp('M');
	}
	// TODO Press I to reset camera back to the origin
	if (input->isKeyDown('i') && input->isKeyDown('I')) {
		glLoadIdentity();
		glutPostRedisplay(); // returns whatever is in the list to its original location.
		input->SetKeyUp('i'); input->SetKeyUp('I');
	}
	// Press D, E and W at the same tiem to toggle development mode
	if (input->isKeyDown('d') && input->isKeyDown('e') && input->isKeyDown('v') ||
		input->isKeyDown('D') && input->isKeyDown('E') && input->isKeyDown('V')) {
		development = !development;
		input->SetKeyUp('d'); input->SetKeyUp('e'); input->SetKeyUp('v');
		input->SetKeyUp('D'); input->SetKeyUp('E');  input->SetKeyUp('V');
	}
	// Put X scale up
	if (input->isKeyDown('x') || input->isKeyDown('X')) {
		scale_x += 0.1;
	}
	// Put Y scale up
	if (input->isKeyDown('y') || input->isKeyDown('Y')) {
		scale_y += 0.1;
	}
	// Put Z scale up
	if (input->isKeyDown('z') || input->isKeyDown('Z')) {
		scale_z += 0.1;
	}
	// Put X scale down
	if (input->isKeyDown('u') || input->isKeyDown('U')) {
		scale_x -= 0.1;
	}
	// Put Y scale down
	if (input->isKeyDown('i') || input->isKeyDown('I')) {
		scale_y -= 0.1;
	}
	// Put Z scale down
	if (input->isKeyDown('o') || input->isKeyDown('O')) {
		scale_z -= 0.1;
	}
	// Put both X  and Y scale down
	if (input->isKeyDown(VK_SPACE)) {
		scale_x -= 0.1;
		scale_z -= 0.1;
	}
	// Camera input controll
	camera->cameraControll(dt, width, height, input);
	// Update object and variables (camera, rotation, etc).
	camera->update();
	float mousePositionX(int width);
	float mousePositionY(int height);

	//xrot += 0.7;	// Rotate On The X Axis
	//yrot += 0.7;	// Rotate On The Y Axis
	//zrot += 0.7;	// Rotate On The Z Axis
	angle += 0.7;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ(),
	          camera->getLookAtX(), camera->getLookAtY(), camera->getLookAtZ(),
			  camera->getUpX(), camera->getUpY(), camera->getUpZ()
	         );
	// Render skybox
	glBindTexture(GL_TEXTURE_2D, *skybox); {
	// Point sampling
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
		glPushMatrix(); {
			glTranslatef(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ());
			glDisable(GL_DEPTH_TEST); {
				shape.drawSkybox();
			}
			glEnable(GL_DEPTH_TEST);
		} glPopMatrix();
	} glBindTexture(GL_TEXTURE_2D, NULL);

	// Render geometry here -------------------------------------
	if (blend) {
		glEnable(GL_BLEND); // Turn blending on
	}
	else {
		glDisable(GL_BLEND); // Turn blending off
	}
	
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	// Stencil buffer settings
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);		// Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);									// Enable the stencil test
	glStencilFunc(GL_ALWAYS, 1, 1);								// Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);					// Set the Stencil Operation to replace values when the test passes
	glDisable(GL_DEPTH_TEST); // Disable the depth test (we don’t want to store depths values while writing to the stencil buffer

	shape.drawFloor(0, .2, 0);									// Draw floor object()
	glEnable(GL_DEPTH_TEST);									// Enable depth test
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);			// Turn on rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);								// Set stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Set the stencil operation to keep all values (we don’t want to change the stencil)

	glPushMatrix(); {
		glScalef(1.0, -1.0, 1.0);								// Flip the scale vertically
		glTranslatef(0, 1, 0);									// Translate down (this will put us under the floor)
		glRotatef(angle, 0, 1, 0);								// Rotate(the shape will be spinning)
		model.render();											// Render a model
	} glPopMatrix();
	
	glDisable(GL_STENCIL_TEST);									// Disable stencil test (no longer needed)
	glEnable(GL_BLEND);											// Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING);										// Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);							// Set colour of floor object
	shape.drawFloor(0, .2, 0);									// Draw floor object
	//glEnable(GL_LIGHTING);									// Enable lighting (rest of scene is lit correctly)
	glDisable(GL_BLEND);										// Disable blend (no longer blending)

	glPushMatrix(); {
		glTranslatef(0, 1, 0);									// Translate(this is where the model will render, distance should match)
		glRotatef(angle, 0, 1, 0);
		model.render();											// Render the real object
	} glPopMatrix();

	//renderLists();
	// Geometry rendering ends here -----------------------------
	// Render text, should be last object rendered.
	glDisable(GL_BLEND); // Turn blending off
	if (development) { renderTextOutput(); }

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
	sprintf_s(cameraPositionText, "Cam Pos: X:%f Y:%f Z:%f", camera->getPositionX(), camera->getPositionY(), camera->getPositionZ());
	sprintf_s(cameraVectorText, "FVector: X:%f Y:%f Z:%f", camera->getForwardX(), camera->getForwardY(), camera->getForwardZ());
	sprintf_s(cameraLookAtText, "LookAt: X:%f Y:%f Z:%f", camera->getLookAtX(), camera->getLookAtY(), camera->getLookAtZ());
	sprintf_s(cameraUpText, "Up: X:%f Y:%f Z:%f", camera->getUpX(), camera->getUpY(), camera->getUpZ());
	sprintf_s(cameraSideText, "Side: X:%f Y:%f Z:%f", camera->getSideX(), camera->getSideY(), camera->getSideZ());
	sprintf_s(cameraRotationText, "Rot: Yaw:%f Pitch:%f Roll:%f", camera->getYaw(), camera->getPitch(), camera->getRoll());
	displayText(-1.f, 0.96f, 0.f, 0.f, 1.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, cameraPositionText);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, cameraVectorText);
	displayText(-1.f, 0.78f, 1.f, 0.f, 0.f, cameraLookAtText);
	displayText(-1.f, 0.72f, 1.f, 0.f, 0.f, cameraUpText);
	displayText(-1.f, 0.66f, 1.f, 0.f, 0.f, cameraSideText);
	displayText(-1.f, 0.60f, 1.f, 0.f, 0.f, cameraRotationText);
	displayText(-1.f, 0.54f, 1.f, 0.f, 0.f, fps);
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

//glPushMatrix(); {
//	glColor4f(0.0f, 1.0f, 0.0f, 0.2f); // Full Brightness, 50% Alpha
//	glBegin(GL_TRIANGLES); // front face
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(-1, -1, 1.5);

//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(1, -1, 1.5);

//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(1, 1, 1.5);
//	glEnd();

//	glBegin(GL_TRIANGLES);
//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(1, 1, 1.5);

//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(-1, 1, 1.5);

//	glNormal3f(0.0f, 0.0f, 1.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(-1, -1, 1.5);
//	glEnd();
//} glPopMatrix();

