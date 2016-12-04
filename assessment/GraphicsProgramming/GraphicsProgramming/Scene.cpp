#include "Scene.h"

Scene::Scene(Input *in) {
	// Store pointer for input class
	input = in;
	// Camera
	camera = &freeCamera;
	//OpenGL settings
	glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
	//glShadeModel(GL_FLAT);						// Enable Flat Shading
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);		// Cornflour Blue Background
	//glClearColor(0.1f, 1.0f, 0.5f, 1.0f);			// Set Clear Color (Greenish Color)
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			// Black Background
	glClearDepth(1.0f);								// Depth Buffer Setup
	glClearStencil(0);								// Clear Stencil Buffer
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
	//glCullFace(GL_BACK);							// Set Culling Face To Back Face
	//glEnable(GL_CULL_FACE);						// Enable Culling
													
	// Other OpenGL / render setting should be applied here.			
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Really Nice Perspective Calculations
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	// For a textured object we can control how the final RGB for the rendered pixel is set (combination of texture and geometry colours)
	glEnable(GL_TEXTURE_2D);										// Enable texturing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);				// Set The Blending Function For Translucency
	glEnable(GL_LIGHTING);											// Enable Lighting
	glEnable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
	// Construct functions
	loadTextures();		// loading textures into vector
	assignTextures();	// assign textures to pointers
	loadModels();		// load 3D models from files
	buildShapes();		// Generate vertices, normals and texture coordinates vectors
	buildLight();		// Set up all lighting arrays
	// Initialise variables
	scale_x = 0;
	scale_y = 0;
	scale_z = 0;

	blend		= false;	// Blending on or off
	wireframe	= false;	// Wireframe on or off
	development = true;		// Turn on or off text rendering	
	// Shadowing
	//populateExample();
	a.set(0.0, 0.0, 0.0);
	b.set(1.0, 1.0, 1.0);
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

	myTexture = SOIL_load_OGL_texture( // 16
		"gfx/doughnut.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 17
		"gfx/texture_earth_clouds.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 18
		"gfx/texture_earth_night.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 19
		"gfx/texture_earth_surface.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 20
		"gfx/texture_jupiter.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 21
		"gfx/texture_mars.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 22
		"gfx/texture_mercury.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 23
		"gfx/texture_moon.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 24
		"gfx/texture_neptune.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 25
		"gfx/texture_saturn.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 26
		"gfx/texture_sun.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 27
		"gfx/texture_venus_atmosphere.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	myTexture = SOIL_load_OGL_texture( // 28
		"gfx/texture_venus_surface.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	); textures.push_back(myTexture);

	for (int i : textures) {
		if (i == NULL) {
			MessageBox(NULL, "Texture failed to load", "help", MB_OK);
		}
	}
}

void Scene::assignTextures() {
	crate_tex			= &textures[0];
	tileBrown_tex		= &textures[1];
	crateArrow_tex		= &textures[2];
	checked_tex			= &textures[3];
	grass_tex			= &textures[4];
	glass_tex			= &textures[5];
	aTrans_tex			= &textures[6];
	crate_trans_tex		= &textures[7];
	skybox_tex			= &textures[8];
	disk_tex			= &textures[9];
	barrel_side_tex		= &textures[10];
	globe_tex			= &textures[11];
	spaceship_tex		= &textures[12];
	barrel_lid_1_tex	= &textures[13];
	barrel_lid_2_tex	= &textures[14];
	barrel_tex			= &textures[15];
	doughnut_tex		= &textures[16];

	earth_clouds_tex	= &textures[17];
	earth_night_tex		= &textures[18];
	earth_surface_tex	= &textures[19];
	jupiter_tex			= &textures[20];
	mars_tex			= &textures[21];
	mercury_tex			= &textures[22];
	moon_tex			= &textures[23];
	neptune_tex			= &textures[24];
	saturn_tex			= &textures[25];
	sun_tex				= &textures[26];
	venus_atmosphere_tex= &textures[27];
	venus_surface_tex	= &textures[28];
}

void Scene::loadModels() {
	spaceship.load("models/spaceship.obj", "models/spaceship.jpg");
	//drone.load("models/drone.obj", "models/EvilDrone_Diff.jpg");
}

void Scene::loadLists() {
	//Torus = glGenLists(1);
	//glNewList(Torus, GL_COMPILE);
	////torus.buildTorus(	2.0, 4.0, 20.0, 10.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, tube edges, torus edges
	////					1, 1, 1,				// scale x, scale y, scale z
	////					3., 7., 3.,				// translate x, translate y, translate z
	////					0., 0., 0., 0);			// rotation angle, rotation x, rotation y, rotation z
	//glEndList();

	//Disc = glGenLists(2);
	//glNewList(Disc, GL_COMPILE);
	//disc_1.render();
	//glEndList();

	//Sphere = glGenLists(2);
	//glNewList(Sphere, GL_COMPILE);
	//sphere.render();
	//glEndList();

	//LowPoliCylinder = glGenLists(3);
	//glNewList(LowPoliCylinder, GL_COMPILE);
	////cylinder.buildCylinder(	2.3f, 20.0f, 10.0f,	// radius, edges, height
	////						1.0f, 1.0f, 1.0f,		// scale x, scale y, scale z
	////						3.0f, 3.0f, 3.0f,		// translate x, translate y, translate z
	////						180.0f, 0.0f, 0.0f, 1.0f);	// rotation angle, rotation x, rotation y, rotation z
	//glEndList();

	//HighPoliCylinder = glGenLists(4);
	//glNewList(HighPoliCylinder, GL_COMPILE);
	////cylinder.buildCylinder(	2.3f, 20.0f, 10.0f,	// radius, edges, height
	////						1.0f, 1.0f, 1.0f,		// scale x, scale y, scale z
	////						3.0f, 3.0f, 3.0f,		// translate x, translate y, translate z
	////						180.0f, 0.0f, 0.0f, 1.0f);	// rotation angle, rotation x, rotation y, rotation z
	//glEndList();
	Floor = glGenLists(1);
	glNewList(Floor, GL_COMPILE);
	floor.render();
	glEndList();
}

void Scene::renderLists() {
	//glCallList(Torus);
	/*glCallList(Sphere);
	glCallList(Disc);
	glCallList(LowPoliCylinder);
	glCallList(HighPoliCylinder);*/
	glCallList(Floor);
	glFlush();
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
	glDisable(GL_DEPTH_TEST);								// Disable the depth test (we don’t want to store depths values while writing to the stencil buffer
	// Draw mirror
	floor.render();
	// Draw floor object()
	glEnable(GL_DEPTH_TEST);								// Enable depth test
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);		// Turn on rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);							// Set stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);					// Set the stencil operation to keep all values (we don’t want to change the stencil)
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
	floor.render();						// Draw floor object
	glEnable(GL_LIGHTING);									// Enable lighting (rest of scene is lit correctly)
	glDisable(GL_BLEND);									// Disable blend (no longer blending)
	// Draw object to reflect
	glPushMatrix(); {
		glTranslatef(0, 0.5, 0);							// Translate(this is where the model will render, distance should match)
		glRotatef(angle, 0, 1, 0);
		model.render();										// Render the real object
	} glPopMatrix();
}

void Scene::renderShadowing() {
	// Generate shadow matrix
	generateShadowMatrix(Light_Position_1, quad.get_verts()->data());
	// Floor for shadowing
	quad.render();
	// Render shadow
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	// Shadow's colour
	glColor3f(0.1f, 0.1f, 0.1f); 
	glPushMatrix(); {
		glMultMatrixf((GLfloat *)shadowMatrix);
		//translate to floor and draw shadow, remember to match any transforms on the object
		glTranslatef(0.f, 1.f, 0.f);
		glRotatef(angle, 0.f, 1.f, 0.f);
		glScalef(1.f, 1.f, 1.f);
		spaceship.render();
	} glPopMatrix();

	glColor3f(1.0f, 1.0f, 1.0f); // S
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	// Render object with corresponding	translate, rotate and scale
	glPushMatrix(); {
		glTranslatef(0.f, 1.f, 0.f);
		glRotatef(angle, 0.f, 1.f, 0.f);
		glScalef(1.f, 1.f, 1.f);
		spaceship.render();
	} glPopMatrix();
}

void Scene::renderStencilShadowing() {
	// Stencil buffer settings
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);	// Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);								// Enable the stencil test
	glStencilFunc(GL_ALWAYS, 1, 1);							// Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);				// Set the Stencil Operation to replace values when the test passes
	glDisable(GL_DEPTH_TEST);								// Disable the depth test (we don’t want to store depths values while writing to the stencil buffer
	// Generate shadow matrix
	generateShadowMatrix(Light_Position_1, quad.get_verts()->data());
	// Shadow surface
	quad.render();
	// Draw floor object()
	// Render shadow
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);								// Enable depth test
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);		// Turn on rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);							// Set stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);					// Set the stencil operation to keep all values (we don’t want to change the stencil)
	// Shadow's colour
	glColor3f(0.1f, 0.1f, 0.1f); 
	glPushMatrix(); {
		glMultMatrixf((GLfloat *)shadowMatrix);
		//translate to floor and draw shadow, remember to match any transforms on the object
		glTranslatef(0.f, 1.f, 0.f);
		glRotatef(angle, 0.f, 1.f, 0.f);
		glScalef(1.f, 1.f, 1.f);
		spaceship.render();
	} glPopMatrix();
	// Draw mirror
	glColor3f(1.0f, 1.0f, 1.0f); // S
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glDisable(GL_STENCIL_TEST);								// Disable stencil test (no longer needed)
	glEnable(GL_BLEND);										// Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING);									// Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);						// Set colour of floor object
	floor.render();			// Draw floor object
	glEnable(GL_LIGHTING);									// Enable lighting (rest of scene is lit correctly)
	glDisable(GL_BLEND);									// Disable blend (no longer blending)
															// Draw object to reflect
	glPushMatrix(); {
		glTranslatef(0.f, 1.f, 0.f);
		glRotatef(angle, 0.f, 1.f, 0.f);
		glScalef(1.f, 1.f, 1.f);
		spaceship.render();
	} glPopMatrix();
}

void Scene::buildShapes() {
	skybox.buildSkybox(GL_TRIANGLES, 
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		skybox_verts, 
		skybox_norms, 
		skybox_texcoords, 
		skybox_tex);

	sphere.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(-8.0f, 0.0f, 0.0f),						// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),						// scale x, scale y, scale z,
		Vector4(0.0, 1.0, 1.0, 1.0),					// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),				// red, green, blue, alpha colour
		earth_clouds_tex);
	//sphere.set_ambient(1, 1, 1, 1);
	//sphere.set_diffuse(1, 1, 1, 1);
	sphere.set_ambient(	0.0f, 0.0f, 0.0f, 1.0f);
	sphere.set_diffuse(	1.0f, 1.0f, 1.0f, 1.0f);
	sphere.set_shininess(120.0f);

	light.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_1),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);

	disc_1.buildDisc(GL_TRIANGLE_FAN, 8.0f, 2.0f,
		Vector3(-6.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	disc_2.buildDisc(GL_TRIANGLE_FAN, 8.0f, 2.0f,		// edges, radius
		Vector3(-4.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	disc_flat.buildDisc(GL_TRIANGLE_FAN, 10, 2,			// edges, radius
		Vector3(-2.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	quad.buildQuad(GL_QUADS,
		Vector3(0.0f, 0.35f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		quad_verts,
		quad_norms,
		quad_texcoords,
		NULL);
	quad.set_ambient(	1.f, 1.f, 1.f, 1.f);
	quad.set_diffuse(	1.f, 1.f, 1.f, 1.f);
	quad.set_specular(	1.f, 1.f, 1.f, 1.f);
	quad.set_shininess(	120.0f );
	quad._scale.set(		1.5, 1.5, 1.5);
	
	circle.buildCircle(	GL_LINE_LOOP, 50,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(2.0f, 2.0f, 2.0f),
		Vector4(90.0, 1.0, 0.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);

	floor.buildQuad(GL_TRIANGLES, 
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 0.5f),
		quad_t_verts,
		quad_t_norms,
		quad_t_texcoords,
		NULL);

	cone.buildCone(GL_TRIANGLES, 2, 10, 10,
		Vector3(3.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);
	cone.set_ambient(0.5, 0, 0, 0);

	cylinder.buildCylinder(GL_TRIANGLES, 2.3f, 20.0f, 10.f,
		Vector3(6.0f, 5.0f, -6.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(180.0f, 1.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		barrel_tex);
	cylinder.set_ambient(1, 1, 1, 1);

	//Torus
	torus.buildTorus(GL_TRIANGLES, 2.0, 4.0, 20.0, 10.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, tube edges, torus edges
		Vector3(12.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	butterfly.createButterfly(GL_LINE_LOOP, 10000,
		Vector3(0.0f, 3.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	// blend_cube
	blend_cube.buildCube(GL_TRIANGLES,
		Vector3(0.0f, 5.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 1.0f, 1.0f, 1.0f),
		Vector4(0.5f, 0.5f, 1.0f, 1.0f),
		cube_verts,
		cube_norms,
		cube_texcoords,
		crate_trans_tex);
	// Solar system
	sun.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,			// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		sun_tex);

	planet_1.buildSphere(GL_TRIANGLES, 0.5f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		mars_tex);

	planet_2.buildSphere(GL_TRIANGLES, 0.3f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		moon_tex);

	planet_3.buildSphere(GL_TRIANGLES, 0.5f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		jupiter_tex);

	planet_4.buildSphere(GL_TRIANGLES, 0.3f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		mercury_tex);

	planet_5.buildSphere(GL_TRIANGLES, 0.5f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		neptune_tex);

	planet_6.buildSphere(GL_TRIANGLES, 0.3f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		saturn_tex);

	planet_7.buildSphere(GL_TRIANGLES, 0.2f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		venus_atmosphere_tex);

	planet_8.buildSphere(GL_TRIANGLES, 0.8f, 15.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		venus_surface_tex);

	torus_orbit.buildTorus(GL_TRIANGLES, 2.0, 4.0, 20.0, 10.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, tube edges, torus edges
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);
}

void Scene::renderShapes() {
	glDisable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
	sphere.render();
	disc_1.render();
	disc_2.render();
	disc_flat.render();
	cone.render();
	cylinder.render();
	torus.render();
	glEnable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
	light.render();
	butterfly.render2D();
}

void Scene::updateVariables() {
	angle += 0.7f;
	/*floor.rotate(angle);
	floor.rotation.setZ(1);
	floor.rotation.setX(1);
	floor.scale.setX(10);
	floor.translate.setX(1);*/
	blend_cube.rotate(angle);
	butterfly.rotate(angle);
	//planet_1.rotate(angle);
	//skybox.rotate(angle);
	light._translate = Light_Position_0;
	setLightPosition(light_x, light_y, light_z, 1.0f, Light_Position_0);
	//sphere.rotate(angle);
}

void Scene::buildLight() {
	// Light 0
	setLightAmbient(1.0f, 1.0f, 1.0f, 1.0f, Light_Ambient_0);
	setLightDiffuse(0.6f, 0.6f, 0.6f, 1.0f, Light_Diffuse_0);			// Light colour
	setLightPosition(0, 3, 0, 1, Light_Position_0);
	setLightSpecular(0.5, 0.5, 0.5, 1.0, Light_Specular_0);
	//setSpotDirection(0.0, 1.0, 0.0, Light_Spot_Direction_0);
	// Light 1
	setLightAmbient(1.0f, 1.0f, 1.0f, 1.0f, Light_Ambient_1);
	setLightDiffuse(0.6f, 0.6f, 0.6f, 1.0f, Light_Diffuse_1);			// Light colour
	setLightPosition(0.0f, 3.0f, 0.0f, 1.0f, Light_Position_1);
	setLightSpecular(0.5f, 0.5f, 0.5f, 1.0f, Light_Specular_1);
	//setLightSpecular(specular, specular, specular, specular, Light_Specular_1);
	//setLightPosition(position_x, position_y, position_z, 1, Light_Position_1);
}

void Scene::renderLight() {
	// Light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse_0);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular_0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light_Spot_Direction_0);
	//glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
	glEnable(GL_LIGHT0);
	
	// Light 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular_1);
	/*glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.125);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);*/
	//glEnable(GL_LIGHT1);
	// Light 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient_0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse_0);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position_0);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light_Specular_0);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.25f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.15f);
	//glEnable(GL_LIGHT2);
}

void Scene::renderSolarSystem() {
	// SOLAR SYSTEM START //
	glPushMatrix(); {
		glTranslatef(0, 8.0f, 0);										// Move entire solar system (Center of the universe is here)
		glScalef(2.0f, 2.0f, 2.0f);										// Scale entire solar system
		glPushMatrix(); { // SUN - start
			glPushMatrix(); {
				glRotatef(angle / 2.0f, 0, 1, 0);						// Rotate sun
				sun.render();											// render sun
			} glPopMatrix();
			// ORBIT 1  START //
			glPushMatrix(); {	// PLANET 1
				glRotatef(angle, 0, 1, 0);								// orbit 1 rotation
				circle.render2D();										// render planet 1 orbit
				glTranslatef(2.0f, 0.0, 0.0);							// translate planet 1 with respect to the sun
				planet_1.render();										// render planet 1
				glPushMatrix(); { // PLANET 2
					glRotatef(-angle - 0.2f, 0, 1, 0);					// planet 2 rotation
					glPushMatrix(); { // planet 2 orbit - start
						glRotatef(angle - 0.4f, 0, 1, 0);				// rotate planet 2 orbit
						glScalef(0.5f, 0.5f, 0.5f);						// scale planet 2 orbit
						circle.render2D();								// render planet 2 orbit
					} glPopMatrix(); // planet 2 orbit - end

					glTranslatef(1, 0, 0);								// translate planet 2 with respect to planet 1
					glRotatef(-angle - 0.5f, 0, 1, 0);					// rotate planet 2
					planet_2.render();									// render planet 2
				} glPopMatrix();
			} glPopMatrix();
			// ORBIT 1 END //
			// ORBIT2 START //
			glPushMatrix(); { // PLANET 1 - start
				glRotatef(angle * 0.5f, 0, 1, 0);						// orbit 2 rotation

				glPushMatrix(); { // planet 1 orbit - start
					glRotatef(angle - 0.2f, 0, 1, 0);					// rotate planet 1 orbit
					glScalef(4.0f, 4.0f, 4.0f);							// scale planet 1 orbit
					circle.render2D();									// render planet 1 orbit
				} glPopMatrix(); // planet 1 orbit - end

				glTranslatef(8.0f, 0, 0);								// translate planet 1 with respect to the sun
				glRotatef(angle * 0.3f, 0, 1, 0);						// rotate planet 1
				planet_3.render();										// render planet 1

				glPushMatrix(); { // PLANET 2 - start
					glRotatef(angle * 0.6f, 0, 1, 0);					// planet 2 rotation

					glPushMatrix(); { // planet 2 orbit - start
						glRotatef(-angle * 0.4f, 0, 1, 0);				// rotate planet 2 orbit
						glScalef(1.25f, 1.25f, 1.25f);					// scale planet 2 orbit
						circle.render2D();								// render planet 2 orbit
					} glPopMatrix(); // planet 2 orbit - end

					glTranslatef(2.5f, 0, 0);							// translate planet 2 with respect to planet 1
					glRotatef(-angle * 0.2f, 0, 1, 0);					// planet 1 rotation
					planet_5.render();									// render planet 2

					glPushMatrix(); { // PLANET 3 - start
						glRotatef(angle -0.3f, 0, 1, 0);				// planet 3 rotation

						glPushMatrix(); { // planet 2 orbit - start
							glRotatef(angle - 0.2f, 0, 1, 0);			// rotate planet 3 orbit
							glScalef(0.5f, 0.5f, 0.5f);					// scale planet 3 orbit
							circle.render2D();							// render planet 3 orbit
						} glPopMatrix(); // planet 2 orbit - end

						glTranslatef(1, 0, 0);							// translate planet 3 with respect to planet 2
						glRotatef(angle - 0.5f, 0, 1, 0);				// planet 2 rotation
						planet_4.render();								// render planet 3
					} glPopMatrix();  // PLANET 3 - end
				} glPopMatrix(); // PLANET 2 - end
			} glPopMatrix(); // PLANET 1 - end
			// ORBIT 2 END //
			// ORBIT 3 START //
			glPushMatrix(); { // PLANET 1 - start
				glRotatef(-angle * 0.5f, 0, 1, 0);						// orbit 3 rotation

				glPushMatrix(); { // planet 1 orbit - start
					glRotatef(angle - 0.2f, 0, 1, 0);					// rotate planet 1 orbit
					glScalef(6.0f, 6.0f, 6.0f);							// scale planet 1 orbit
					circle.render2D();									// render planet 1 orbit
				} glPopMatrix(); // planet 1 orbit - end

				glTranslatef(12.0f, 0, 0);								// translate planet 1

				glPushMatrix(); {
					glRotatef(angle * 0.5f, 0, 1, 0);					// planet 1 rotation
					planet_6.render();									// render planet 1
				} glPopMatrix();

				glPushMatrix(); { // PLANET 2 - start
				//glRotatef(-angle * 0.6f, 0, 1, 0);						// planet 1 rotation

					glPushMatrix(); {									// planet 1 orbit - start
						glRotatef(45.0f, 0, 0, 1);						// crook planet 1 orbit
						glRotatef(-angle - 0.2f, 0, 1, 0);				// rotate planet 1 orbit
						glScalef(0.2f, 0.2f, 0.2f);						// scale planet 1 orbit into elipse
						torus_orbit.render();									// render planet 1 orbit
					} glPopMatrix();									// planet 1 orbit - end

					glTranslatef(1, 0, 0);									// translate planet 2 with respect to planet 1

					glPushMatrix(); {
						glRotatef(angle * 0.7f, 0, 1, 0);						// planet 2 rotation
						planet_7.render();										// render planet 2
					} glPopMatrix();
				} glPopMatrix();  // PLANET 2 - end
			} glPopMatrix(); // PLANET 1 - end
			// ORBIT 3 END //
			// ORBIT 4 START //
			glPushMatrix(); { // PLANET 1 - start
				glRotatef(-angle, 0, 1, 0);								// orbit 4 rotation

				glPushMatrix(); {										// planet 1 orbit - start
					glRotatef(-angle - 0.2f, 0, 1, 0);					// rotate planet 1 orbit
					glScalef(8.0f, 8.0f, 8.0f);							// scale planet 1 orbit
					circle.render2D();									// render planet 1 orbit
				} glPopMatrix();										// planet 1 orbit - end

				glTranslatef(16.0f, 0, 0);								// translate planet 1 with respect to the sun
				glRotatef(angle * 2.0f, 0, 1, 0);					// planet 2 rotation
				planet_8.render();										// render planet 1

				glPushMatrix(); {										// planet 1 orbit - start
					glRotatef(45.0f, 0, 0, 1);							// crook planet 1 orbit
					glRotatef(-angle - 0.2f, 0, 1, 0);					// rotate planet 1 orbit
					glScalef(2.0f, 1, 1);								// scale planet 1 orbit into elipse
					circle.render2D();									// render planet 1 orbit
				} glPopMatrix();										// planet 1 orbit - end

				glPushMatrix(); {										// planet 1 orbit - start
					glRotatef(45.0f, 0, 0, 1);							// crook planet 1 orbit
					glRotatef(angle - 0.2f, 0, 1, 0);					// rotate planet 1 orbit
					glScalef(2.0f, 1, 1);								// scale planet 1 orbit into elipse
					circle.render2D();									// render planet 1 orbit
				} glPopMatrix();										// planet 1 orbit - end
			} glPopMatrix(); // PLANET 1 - end
			// ORBIT 4 END //
		} glPopMatrix(); // SUN - end
	} glPopMatrix();
	// SOLAR SYSTEM END //
}
// TODO
void Scene::renderFloor() {
}
// TODO
void Scene::renderWalls() {
}
// TODO
void Scene::renderPlanets() {

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
	if (input->isKeyDown('v') || input->isKeyDown('V')) {
		development = !development;
		input->SetKeyUp('v'); input->SetKeyUp('V');
	}
	// Put X scale up
	if (input->isKeyDown('x') || input->isKeyDown('X')) {
		scale_x += 0.1f;
	}
	// Put Y scale up
	if (input->isKeyDown('y') || input->isKeyDown('Y')) {
		scale_y += 0.1f;
	}
	// Put Z scale up
	if (input->isKeyDown('z') || input->isKeyDown('Z')) {
		scale_z += 0.1f;
	}
	// Put X scale down
	if (input->isKeyDown('u') || input->isKeyDown('U')) {
		scale_x -= 0.1f;
	}
	// Put Y scale down
	if (input->isKeyDown('i') || input->isKeyDown('I')) {
		scale_y -= 0.1f;
	}
	// Put Z scale down
	if (input->isKeyDown('o') || input->isKeyDown('O')) {
		scale_z -= 0.1f;
	}
	// Put both X  and Y scale down
	if (input->isKeyDown(32)) { // 32 - ASCII space code, (13 - enter)
		scale_x -= 0.1f;
		scale_z -= 0.1f;
	}
	// Light controlls
	// move light's position right
	if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
		light_x += 0.1f;
	}
	// move light's position left
	if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
		light_x -= 0.1f;
	}
	// move light's position up
	if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
		light_y += 0.1f;
	}
	// move light's position down
	if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
		light_y -= 0.1f;
	}
	// move light's position z towards
	if (input->isKeyDown('g') || input->isKeyDown('G')) {
		light_z += 0.1f;
	}
	// move light's position z inwards
	if (input->isKeyDown('t') || input->isKeyDown('T')) {
		light_z -= 0.1f;
	}
	if (input->isKeyDown('l') || input->isKeyDown('L')) {
		light_0 = !light_0;
		light_1 = !light_1;
		input->SetKeyUp('l'); input->SetKeyUp('L');
	}
	// Camera input controll
	float mousePositionX(int width);
	float mousePositionY(int height);
	camera->cameraControll(dt, width, height, input);
	camera->update();
	// Update object and variables (camera, rotation, etc).
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
	gluLookAt(	camera->getPositionX(), camera->getPositionY(), camera->getPositionZ(),
				camera->getLookAtX(), camera->getLookAtY(), camera->getLookAtZ(),
				camera->getUpX(), camera->getUpY(), camera->getUpZ() );
	// Render skybox
	// Point sampling
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
	glPushMatrix(); {
		glTranslatef(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ());
		glDisable(GL_DEPTH_TEST); {
			skybox.render();
		}
		glEnable(GL_DEPTH_TEST);
	} glPopMatrix();
	// Lighting
	renderLight();
	// Shadowing
	//renderShadowing();
	//renderStencilShadowing();
	// Render geometry here -------------------------------------
	// Stencil buffer
	renderStencilBuffer(spaceship);
	// Blend cube
	setRenderMode(blend, wireframe);
	blend_cube.renderBlend();
	setRenderMode(blend, wireframe);
	// Render shapes
	renderShapes();
	// Solar system
	renderSolarSystem();
	// Render floor
	renderFloor();
	// Render walls
	renderWalls();
	// Render planets for lighting testing
	renderPlanets();
	// Geometry rendering ends here -----------------------------
	// Render text, should be last object rendered.
	setRenderMode(blend, wireframe);
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

void Scene::renderTextOutput() {
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
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::setLightAmbient(float x, float y, float z, float w, GLfloat* lightAmbient) {
	lightAmbient[0] = x;
	lightAmbient[1] = y;
	lightAmbient[2] = z;
	lightAmbient[3] = w;
}

void Scene::setLightDiffuse(float x, float y, float z, float w, GLfloat* lightDiffuse) {
	lightDiffuse[0] = x;
	lightDiffuse[1] = y;
	lightDiffuse[2] = z;
	lightDiffuse[3] = w;
}

void Scene::setLightPosition(float x, float y, float z, float w, GLfloat* lightPosition) {
	lightPosition[0] = x;
	lightPosition[1] = y;
	lightPosition[2] = z;
	lightPosition[3] = w;
}

void Scene::setSpotDirection(float x, float y, float z, GLfloat* spotDirection) {
	spotDirection[0] = x;
	spotDirection[1] = y;
	spotDirection[2] = z;
	//spotDirection[3] = w;
}

void Scene::setLightSpecular(float x, float y, float z, float w, GLfloat* lightSpecular) {
	lightSpecular[0] = x;
	lightSpecular[1] = y;
	lightSpecular[2] = z;
	lightSpecular[3] = w;
}

// Shadowing
// Generates a shadow matrix.
// The shadow matrix will transform an object into a 2D shadow of itself, based on the provide light position and floor plane.
// shadowMatrix[16]; must be declared
// Inputs: light_pos is the light position. floor is a vertex array with 4 vertices that draw a quad (defining the floor plane that the shadow will be drawn on)
void Scene::generateShadowMatrix(float light_pos[4], GLfloat floor[12]) {

	//Defining vertices of plane are PQR with edges PQ and PR
	Vector3 P(floor[0], floor[1], floor[2]);	//top left
	Vector3 Q(floor[3], floor[4], floor[5]);	// bottom left
	Vector3 R(floor[9], floor[10], floor[11]);	// top right

	Vector3 PQ = (Q - P).normalised();
	Vector3 PR = (R - P).normalised();
	Vector3 normal = PR.cross(PQ);

	//Equation of plane is ax + by + cz = d
	//a, b and c are the coefficients of the normal to the plane (i.e. normal = ai + bj + ck)
	//If (x0, y0, z0) is any point on the plane, d = a*x0 + b*y0 + c*z0
	//i.e. d is the dot product of any point on the plane (using P here) and the normal to the plane
	float a, b, c, d;
	a = normal.getX();
	b = normal.getY();
	c = normal.getZ();
	d = normal.dot(P);

	//Origin of projection is at x, y, z. Projection here originating from the light source's position
	float x, y, z;
	x = light_pos[0];
	y = light_pos[1];
	z = light_pos[2];

	//This is the general perspective transformation matrix from a point (x, y, z) onto the plane ax + by + cz = d
	shadowMatrix[0] = d - (b * y + c * z);
	shadowMatrix[1] = a * y;
	shadowMatrix[2] = a * z;
	shadowMatrix[3] = a;

	shadowMatrix[4] = b * x;
	shadowMatrix[5] = d - (a * x + c * z);
	shadowMatrix[6] = b * z;
	shadowMatrix[7] = b;

	shadowMatrix[8] = c * x;
	shadowMatrix[9] = c * y;
	shadowMatrix[10] = d - (a * x + b * y);
	shadowMatrix[11] = c;

	shadowMatrix[12] = -d * x;
	shadowMatrix[13] = -d * y;
	shadowMatrix[14] = -d * z;
	shadowMatrix[15] = -(a * x + b * y + c * z);
}

