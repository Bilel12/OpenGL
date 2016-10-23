#include "Scene.h"

Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	
	//OpenGL settings
	
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	// Other OpenGL / render setting should be applied here.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //For a textured object we can control how the final RGB for the rendered pixel is set (combination of texture and geometry colours)
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					// Set The Blending Function For Translucency
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);			// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	for (loop = 0;loop<MAX_PARTICLES;++loop)				// Initials All The Textures
	{
		particle[loop].active = true;								// Make All The Particles Active
		particle[loop].life = 1.0f;								// Give All The Particles Full Life
		particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
		particle[loop].r = colors[loop*(12 / MAX_PARTICLES)][0];	// Select Red Rainbow Color
		particle[loop].g = colors[loop*(12 / MAX_PARTICLES)][1];	// Select Red Rainbow Color
		particle[loop].b = colors[loop*(12 / MAX_PARTICLES)][2];	// Select Red Rainbow Color
		particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
		particle[loop].xg = 0.0f;									// Set Horizontal Pull To Zero
		particle[loop].yg = -0.8f;								// Set Vertical Pull Downward
		particle[loop].zg = 0.0f;									// Set Pull On Z Axis To Zero
	}
	// loading textures into vector
	loadTextures();
	
	// Initialise variables
	triangle = &textures[2];
	checked = &textures[3];
	grass = &textures[4];
	glass = &textures[5];
	particle_texture = &textures[6];
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

	myTexture = SOIL_load_OGL_texture( // 6
		"gfx/particle.bmp",
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
	// If Number Pad 8 And Y Gravity Is Less Than 1.5 Increase Pull Upwards
	if (input->isKeyDown(VK_NUMPAD8) && (particle[loop].yg<1.5f)) particle[loop].yg += 0.01f;

	// If Number Pad 2 And Y Gravity Is Greater Than -1.5 Increase Pull Downwards
	if (input->isKeyDown(VK_NUMPAD2) && (particle[loop].yg>-1.5f)) particle[loop].yg -= 0.01f;

	// If Number Pad 6 And X Gravity Is Less Than 1.5 Increase Pull Right
	if (input->isKeyDown(VK_NUMPAD6) && (particle[loop].xg<1.5f)) particle[loop].xg += 0.01f;

	// If Number Pad 4 And X Gravity Is Greater Than -1.5 Increase Pull Left
	if (input->isKeyDown(VK_NUMPAD4) && (particle[loop].xg>-1.5f)) particle[loop].xg -= 0.01f;

	if (input->isKeyDown('e'))										// Tab Key Causes A Burst
	{
		particle[loop].x = 0.0f;								// Center On X Axis
		particle[loop].y = 0.0f;								// Center On Y Axis
		particle[loop].z = 0.0f;								// Center On Z Axis
		particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;	// Random Speed On X Axis
		particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;	// Random Speed On Y Axis
		particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;	// Random Speed On Z Axis
	}
	// Toggle blend
	if (input->isKeyDown('b') || input->isKeyDown('B')) {
		blend = !blend; // toggle blend (true/false)
		if (blend) {
			glEnable(GL_BLEND); // Turn blending on
			glDisable(GL_DEPTH_TEST); // Turn depth testing off
		}
		else {
			glDisable(GL_BLEND); // Turn blending off
			glEnable(GL_DEPTH_TEST); // Turn depth testing on
		}
		input->SetKeyUp('b'); input->SetKeyUp('B');
		/*blend = !blend;
		if (blend) {
			glEnable(GL_BLEND);
			glDisable(GL_TEXTURE_DEPTH);
		} else {
			glDisable(GL_BLEND);
			glEnable(GL_TEXTURE_DEPTH);
		}

		input->SetKeyUp('b'); input->SetKeyUp('B');*/
	}
	// move camera forward
	if (input->isKeyDown('w') || input->isKeyDown('w')) {
		camera.moveForward(dt);
		zoom -= 0.2f;
	}
	// move camera backwards
	if (input->isKeyDown('s') || input->isKeyDown('S')) {
		camera.moveBackwards(dt);
		zoom += 0.2f;
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
	glPushMatrix(); {
		glBindTexture(GL_TEXTURE_2D, *particle_texture);
		for (loop = 0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
		{
			if (particle[loop].active)							// If The Particle Is Active
			{
				float x = particle[loop].x;						// Grab Our Particle X Position
				float y = particle[loop].y;						// Grab Our Particle Y Position
				float z = particle[loop].z + zoom;					// Particle Z Pos + Zoom

																	// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				glColor4f(particle[loop].r, particle[loop].g, particle[loop].b, particle[loop].life);

				glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
				glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
				glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
				glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
				glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
				glEnd();										// Done Building Triangle Strip

				particle[loop].x += particle[loop].xi / (slowdown * 1000);// Move On The X Axis By X Speed
				particle[loop].y += particle[loop].yi / (slowdown * 1000);// Move On The Y Axis By Y Speed
				particle[loop].z += particle[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

				particle[loop].xi += particle[loop].xg;			// Take Pull On X Axis Into Account
				particle[loop].yi += particle[loop].yg;			// Take Pull On Y Axis Into Account
				particle[loop].zi += particle[loop].zg;			// Take Pull On Z Axis Into Account
				particle[loop].life -= particle[loop].fade;		// Reduce Particles Life By 'Fade'

				if (particle[loop].life < 0.0f)					// If Particle Is Burned Out
				{
					particle[loop].life = 1.0f;					// Give It New Life
					particle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Value
					particle[loop].x = 0.0f;						// Center On X Axis
					particle[loop].y = 0.0f;						// Center On Y Axis
					particle[loop].z = 0.0f;						// Center On Z Axis
					particle[loop].xi = xspeed + float((rand() % 60) - 32.0f);	// X Axis Speed And Direction
					particle[loop].yi = yspeed + float((rand() % 60) - 30.0f);	// Y Axis Speed And Direction
					particle[loop].zi = float((rand() % 60) - 30.0f);	// Z Axis Speed And Direction
					particle[loop].r = colors[col][0];			// Select Red From Color Table
					particle[loop].g = colors[col][1];			// Select Green From Color Table
					particle[loop].b = colors[col][2];			// Select Blue From Color Table
				}
			}
		}
		glEnd();
	} glPopMatrix();

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
	farPlane = 200.0f;

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
