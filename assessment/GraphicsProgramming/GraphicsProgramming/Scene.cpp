#include "Scene.h"

Scene::Scene(Input *in) {
	// Store pointer for input class
	input = in;
	// Camera
	camera = &freeCamera;
	//OpenGL settings
	frame = 0; timebase = 0;
	glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
	glShadeModel(GL_FLAT);
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);		// Cornflour Blue Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			// Black Background
	glClearDepth(1.0f);								// Depth Buffer Setup
	glClearStencil(0);								// Clear Stencil Buffer
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	//glDisable(GL_DEPTH_TEST);						// Disable Depth Testing
	glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do

	// Other OpenGL / render setting should be applied here.			
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Really Nice Perspective Calculations
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//For a textured object we can control how the final RGB for the rendered pixel is set (combination of texture and geometry colours)
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);				// Set The Blending Function For Translucency

	loadTextures();// loading textures into vector
	assignTextures();// assign textures to pointers
	loadModels();// load 3D models from files
	//loadLists();// load lists
	buildShapes();
	// Initialise variables
	xrot = 0.0;				// Rotate On The X Axis
	yrot = 0.0;				// Rotate On The Y Axis
	zrot = 0.0;				// Rotate On The Z Axis
	angle = 0.0;			// Rotate by angle
	position_x = 0, position_y = 0, position_z = 0;
	scale_x = 0, scale_y = 0, scale_z = 0;
	blend = false;			// Blending on or off
	wireframe = false;		// Wireframe on or off
	development = true;		// Turn on or off text rendering		
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
		"gfx/barrel_side.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 11
		"gfx/globe1.png",
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

	myTexture = SOIL_load_OGL_texture( // 13
		"gfx/barrel_lid_1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 14
		"gfx/barrel_lid_2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 15
		"gfx/barrel.png",
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
	crate_tex = &textures[0];
	tileBrown_tex = &textures[1];
	crateArrow_tex = &textures[2];
	checked_tex = &textures[3];
	grass_tex = &textures[4];
	glass_tex = &textures[5];
	aTrans_tex = &textures[6];
	crate_trans_tex = &textures[7];
	skybox_tex = &textures[8];
	disk_tex = &textures[9];
	barrel_side_tex = &textures[10];
	globe_tex = &textures[11];
	spaceship_tex = &textures[12];
	barrel_lid_1_tex = &textures[13];
	barrel_lid_2_tex = &textures[14];
	barrel_tex = &textures[15];
}

void Scene::loadModels() {
	spaceship.load("models/spaceship.obj", "models/spaceship.jpg");
	//drone.load("models/drone.obj", "models/EvilDrone_Diff.jpg");
}

void Scene::loadLists() {
	Torus = glGenLists(1);
	glNewList(Torus, GL_COMPILE);
	draw.drawSphereTorus(100, 3.0, 0.0, 0.0, 0.1);
	glEndList();

	Disc = glGenLists(2);
	glNewList(Disc, GL_COMPILE);
	shape.renderDisc(disk_tex);
	glEndList();

	Sphere = glGenLists(2);
	glNewList(Sphere, GL_COMPILE);
	shape.renderSphere(globe_tex);
	glEndList();

	LowPoliCylinder = glGenLists(3);
	glNewList(LowPoliCylinder, GL_COMPILE);
	draw.drawCylinderTwoTex(3., 6., 3., -5., 0., -1., disk_tex, globe_tex);
	glEndList();

	HighPoliCylinder = glGenLists(4);
	glNewList(HighPoliCylinder, GL_COMPILE);
	draw.drawCylinderOneTex(3., 100., 3., 5., 0., -1., disk_tex);
	glEndList();
}

void Scene::renderLists() {
	//glCallList(Torus);
	glCallList(Sphere);
	glCallList(Disc);
	//glCallList(LowPoliCylinder);
	//glCallList(HighPoliCylinder);
	glFlush();
}

void Scene::drawShapes() {
	//draw.drawCylinder(2., 50., 10., 3., 3., 3., disk_tex);
	//draw.drawCylinderTwoTex(2., 10., 20., 3., 3., 3., barrel_lid_1_tex, barrel_side_tex);
	//draw.drawCylinderOneTex(2., 10., 20., 3., 3., 3., barrel_tex);
}

void Scene::setRenderMode(bool blend, bool wireframe) {
	if (blend) glEnable(GL_BLEND);								// Turn blending on
	else glDisable(GL_BLEND);									// Turn blending off

	if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }	// Turn wireframe on
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);				// Turn wireframe off
}

void Scene::renderStencilBuffer(Model model) {
	// Stencil buffer settings
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);	// Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);								// Enable the stencil test
	glStencilFunc(GL_ALWAYS, 1, 1);							// Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);				// Set the Stencil Operation to replace values when the test passes
	glDisable(GL_DEPTH_TEST);								// Disable the depth test (we don�t want to store depths values while writing to the stencil buffer
	// Draw mirror
	floor.renderFloor(0.5, 0.5, 0.5, 0.5);					
	// Draw floor object()
	glEnable(GL_DEPTH_TEST);								// Enable depth test
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);		// Turn on rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);							// Set stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);					// Set the stencil operation to keep all values (we don�t want to change the stencil)
	// Draw reflection
	glPushMatrix(); {
		glScalef(1.0, -1.0, 1.0);							// Flip the scale vertically
		glTranslatef(0, 1, 0);								// Translate down (this will put us under the floor)
		glRotatef(angle, 0, 1, 0);							// Rotate(the shape will be spinning)
		model.render();										// Render a model
	} glPopMatrix();
	// Draw mirror
	glDisable(GL_STENCIL_TEST);								// Disable stencil test (no longer needed)
	glEnable(GL_BLEND);										// Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING);									// Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);						// Set colour of floor object
	floor.renderFloor(0.5, 0.5, 0.5, 0.5);					// Draw floor object
	//glEnable(GL_LIGHTING);								// Enable lighting (rest of scene is lit correctly)
	glDisable(GL_BLEND);									// Disable blend (no longer blending)
	// Draw object to reflect
	glPushMatrix(); {
		glTranslatef(0, 0.1, 0);							// Translate(this is where the model will render, distance should match)
		glRotatef(angle, 0, 1, 0);
		model.render();										// Render the real object
	} glPopMatrix();
}

void Scene::buildShapes() {
	sphere.buildSphere( 2.0, 15.0, 15.0,
						1, 1, 1,
						0, 0, -5,
						angle, 0, 1, 0 );
	disc_1.buildDisc(10, 2, 1, 1, 1, -3, 3, 3, 1, 1, 1, 1);
	disc_2.buildDisc(200, 2, 1, 1, 1, 3, 3, 3, 1, 1, 1, 1);
	disc_flat.buildDisc(10, 2, 1, 1, 1, -3, -3, -3, 90, 1, 0, 0);
	circle.buildCircle(50, 1, 1, 1, -5, 0, 0, 0, 1, 1, 1);
	//shape.buildFlatDisc(200.0, 2.0, -7.0, -5.0);
	cone.buildCone(2.0, 10.0, 10.0, 5.0, 5.0, -10.);
	floor.buildFloor(1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
	//shape.buildCircle(60.0, 1., 1., 1.);
	cylinder.buildCylinder(2., 20., 7., 3., 3., 3.);
}

void Scene::renderShapes() {
	//draw.drawCylinder(2.0, 200.0, 3.0, 0.0, 5.0, -5.0, barrel_tex);
	
	sphere.renderSphere(globe_tex);
	disc_1.renderDisc(disk_tex);
	disc_2.renderDisc(barrel_lid_2_tex);
	disc_flat.renderDisc(disk_tex);
	circle.renderCircle();
	//shape.renderFlatDisc(disk_tex);
	cone.renderCone(disk_tex);
	cylinder.renderCylinder(barrel_tex);
	//shape.renderCircle();
	//shape.drawSphereTorus(100, scale_x, scale_y, scale_z, 0.23); // frame rate starts droping at rot_interval < 0.13 on MAC < 0.23 on Uni PCs
	//shape.drawIcosahedron();
	//shape.drawIcosahedron();
}

void Scene::updateVariables() {
	//xrot += 0.7;	// Rotate On The X Axis
	//yrot += 0.7;	// Rotate On The Y Axis
	//zrot += 0.7;	// Rotate On The Z Axis
	angle += 0.7;
	/*floor.rotate(angle);
	floor.rotation.setZ(1);
	floor.rotation.setX(1);
	floor.scale.setX(10);
	floor.translate.setX(1);*/
	blend_cube.translate.set(-3, 0, 1);
	blend_cube.scale.set(1, 1, 1);
	blend_cube.rotation.set(1, 1, 1);
	blend_cube.rotate(angle);
	sphere.rotate(angle);
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
	if (input->isKeyDown('m') || input->isKeyDown('M')) {
		wireframe = !wireframe; // toggle wireframe (true/false)
		input->SetKeyUp('m'); input->SetKeyUp('M');
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
	//
	updateVariables();

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
	
	// Point sampling
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
		glPushMatrix(); {
			glTranslatef(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ());
			glDisable(GL_DEPTH_TEST); {
				shape.renderSkybox(skybox_tex);
			}
			glEnable(GL_DEPTH_TEST);
		} glPopMatrix();

	// Render geometry here -------------------------------------
	renderStencilBuffer(spaceship);
	setRenderMode(blend, wireframe);
	blend_cube.renderBlendCube(crate_trans_tex);
	setRenderMode(blend, wireframe);
	renderShapes();
	drawShapes();

	setRenderMode(blend, wireframe);
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

