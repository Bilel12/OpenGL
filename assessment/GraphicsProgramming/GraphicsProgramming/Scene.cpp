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
	setMaterials();		// Set up materials on shapes
	buildLight();		// Set up all lighting arrays
	// Initialise variables
	scale_x = 0;
	scale_y = 0;
	scale_z = 0;
	// Booleans
	blend		= false;	// Blending on or off
	wireframe	= false;	// Wireframe on or off
	development = true;		// Turn on or off text rendering

	light_0		= true;
	light_1		= false;
	light_2		= false;
	light_3		= false;
	light_4		= false;
	light_5		= false;
	// Texture filtering
	point			= false;
	biliner			= false;
	mipmapping		= false;
	half_mipmapping	= false;
	half_trilinear	= false;
	trilinear		= false;
	right			= true;
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

	myTexture = SOIL_load_OGL_texture( // 29
		"gfx/blue.png",
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

	blue_tex = &textures[29];
}

void Scene::loadModels() {
	spaceship.load("models/spaceship.obj", "models/spaceship.jpg");
	//drone.load("models/drone.obj", "models/EvilDrone_Diff.jpg");
}

void Scene::setRenderMode(bool blend, bool wireframe) {
	if (blend) glEnable(GL_BLEND);								// Turn blending on
	else glDisable(GL_BLEND);									// Turn blending off

	if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }	// Turn wireframe on
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);				// Turn wireframe off
}

void Scene::renderStencilBuffer() {
	// Stencil buffer settings
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);	// Turn off writing to the frame buffer
	glEnable(GL_STENCIL_TEST);								// Enable the stencil test
	glStencilFunc(GL_ALWAYS, 1, 1);							// Set the stencil function to always pass
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);				// Set the Stencil Operation to replace values when the test passes
	glDisable(GL_DEPTH_TEST);								// Disable the depth test (we don’t want to store depths values while writing to the stencil buffer
	// Draw mirror (Get stencil shape)
	floor.render();
	// Draw floor object()
	glEnable(GL_DEPTH_TEST);								// Enable depth test
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);		// Turn on rendering to the frame buffer
	glStencilFunc(GL_EQUAL, 1, 1);							// Set stencil function to test if the value is 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);					// Set the stencil operation to keep all values (we don’t want to change the stencil)
	// Draw reflection
	//////////////////
	glPushMatrix(); {
		glScalef(1.0, -1.0, 1.0);							// Flip the scale vertically
		glTranslatef(0, 1, 0);							// Translate up (this will put us above the floor)
		glRotatef(angle, 0, 1, 0);							// Rotate(the shape will be spinning)
		//spaceship.render();									// Render a model
		renderSolarSystem();
	} glPopMatrix();
	//////////////////
	// Draw mirror
	glDisable(GL_STENCIL_TEST);								// Disable stencil test (no longer needed)
	glEnable(GL_BLEND);										// Enable alpha blending (to combine the floor object with model)
	glDisable(GL_LIGHTING);									// Disable lighting (100% reflective object)
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);						// Set colour of floor object
	floor.render();											// Draw floor object
	glEnable(GL_LIGHTING);									// Enable lighting (rest of scene is lit correctly)
	glDisable(GL_BLEND);									// Disable blend (no longer blending)
	// Draw object to reflect
	//////////////////////////
	glPushMatrix(); {
		glTranslatef(0, 1.7f, 0);							// Translate(this is where the model will render, distance should match)
		glRotatef(angle, 0, 1, 0);
		//spaceship.render();										// Render the real object
		renderSolarSystem();
	} glPopMatrix();
	//////////////////////////
}

void Scene::renderShadowing() {
	// Generate shadow matrix
	generateShadowMatrix(Light_Position_2, quad.get_verts()->data());
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
		//glTranslatef(Light_Position_6[0], Light_Position_6[1], Light_Position_6[2]);
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
	skybox.buildFromArray(GL_TRIANGLES,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		skybox_verts,
		skybox_norms,
		skybox_texcoords,
		skybox_tex);
	// Sphere's for material altering
	// 5x5 spheres
	sphere_1.buildSphere(GL_TRIANGLES, 0.5f, 5.0f, 5.0f,	// radius, latitude, longitude
		Vector3(0.0f, 2.0f, 0.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 10x10 sphere
	sphere_2.buildSphere(GL_TRIANGLES, 0.5f, 10.0f, 10.0f,	// radius, latitude, longitude
		Vector3(0.0f, 2.0f, -2.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 15x15 sphere
	sphere_3.buildSphere(GL_TRIANGLES, 0.5f, 10.0f, 15.0f,	// radius, latitude, longitude
		Vector3(0.0f, 2.0f, -4.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 15x10 sphere
	sphere_4.buildSphere(GL_TRIANGLES, 0.5f, 15.0f, 10.0f,	// radius, latitude, longitude
		Vector3(0.0f, 2.0f, -6.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 30x30 sphere
	sphere_5.buildSphere(GL_TRIANGLES, 0.5f, 30.0f, 30.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, 0.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 45x30 sphere
	sphere_6.buildSphere(GL_TRIANGLES, 0.5f, 45.0f, 30.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, -2.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 80x80 sphere
	sphere_7.buildSphere(GL_TRIANGLES, 0.5f, 80.0f, 80.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, -4.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	// 160x160 sphere
	sphere_8.buildSphere(GL_TRIANGLES, 0.5f, 160.0f, 160.0f,	// radius, latitude, longitude
		Vector3(0.0f, 0.0f, -6.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 0.0, 1.0, 0.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		blue_tex);
	
	disc_1.buildDisc(GL_TRIANGLE_FAN, 32.0f, 2.0f,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 0.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	disc_2.buildDisc(GL_TRIANGLE_FAN, 8.0f, 2.0f,		// edges, radius
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 0.0, 1.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	disc_3.buildDisc(GL_TRIANGLE_FAN, 6.0f, 2.0f,		// edges, radius
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 0.0, 0.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	quad.buildFromArray(GL_QUADS,
		Vector3(0.0f, 0.35f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		quad_verts,
		quad_norms,
		quad_texcoords,
		NULL);
	// TODO
	quad.set_ambient(1.f, 1.f, 1.f, 1.f);
	quad.set_diffuse(1.f, 1.f, 1.f, 1.f);
	quad.set_specular(1.f, 1.f, 1.f, 1.f);
	quad.set_shininess(120.0f);
	quad._scale.set(1.5, 1.5, 1.5);

	circle.buildCircle(GL_LINE_LOOP, 50,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(2.0f, 2.0f, 2.0f),
		Vector4(90.0, 1.0, 0.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);

	floor.buildFromArray(GL_TRIANGLES,
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(20.0f, 20.0f, 25.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 0.5f),
		quad_t_verts,
		quad_t_norms,
		quad_t_texcoords,
		NULL);

	main_floor.buildFromArray(GL_TRIANGLES,
		Vector3(0.0f, 2.0f, 0.0f),
		Vector3(20.0f, 20.0f, 25.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 0.5f),
		quad_t_verts,
		quad_t_norms,
		quad_t_texcoords,
		grass_tex);

	cone_1.buildCone(GL_TRIANGLES, 2.0f, 10.0f, 10.0f,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 0.0, 1.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	cone_2.buildCone(GL_TRIANGLES, 2.0f, 10.0f, 10.0f,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 0.0, 1.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	cylinder_1.buildCylinder(GL_TRIANGLES, 2.3f, 20.0f, 10.f,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		barrel_tex);

	cylinder_2.buildCylinder(GL_TRIANGLES, 2.3f, 20.0f, 10.f,
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector4(1.0f, 0.0f, 1.0f, 0.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		barrel_tex);

	//Toruses
	torus_1.buildTorus(GL_TRIANGLES, 2.0, 4.0, 20.0, 10.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges
		Vector3(12.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	torus_2.buildTorus(GL_TRIANGLES, 2.0, 4.0, 32.0, 32.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges
		Vector3(12.0f, 0.0f, 8.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(45.0, 1.0, 0.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	torus_3.buildTorus(GL_TRIANGLES, 2.0, 4.0, 64.0, 64.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges
		Vector3(12.0f, 4.0f, 4.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(-45.0, 1.0, 0.0, 0.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	torus_pres.buildTorus(GL_TRIANGLES, 2.0, 4.0, 128.0, 128.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges
		Vector3(15.0f, 6.0f, 20.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	torus_three.buildTorus(GL_TRIANGLES, 1.0, 2.0, 3.0, 32.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges 
		Vector3(-14.0f, 7.0f, 20.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	torus_three_1.buildTorus(GL_TRIANGLES, 1.0, 2.0, 32.0, 3.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges
		Vector3(-10.0f, 4.0f, 18.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);

	disc_pres.buildDisc(GL_TRIANGLE_FAN, 128.0f, 2.0f,		// edges, radius
		Vector3(2.0f, 3.0f, 10.0f),
		Vector3(2.0f, 2.0f, 2.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	cylinder_pres.buildCylinder(GL_TRIANGLES, 2.3f, 20.0f, 10.f,
		Vector3(0.0f, -8.0f, 20.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector4(0.0f, 1.0f, 1.0f, 1.0f),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		barrel_tex);

	sphere_pres.buildSphere(GL_TRIANGLES, 2.0f, 64.0f, 64.0f,	// radius, latitude, longitude
		Vector3(-5.0f, 3.0f, 20.0f),							// translate x, translate y, translate z,
		Vector3(1.0f, 1.0f, 1.0f),							// scale x, scale y, scale z,
		Vector4(0.0, 1.0, 1.0, 1.0),						// rotation angle, rotation x, rotation y, rotation z
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),					// red, green, blue, alpha colour
		earth_clouds_tex);

	cone_pres.buildCone(GL_TRIANGLES, 2.0f, 64.0f, 5.0f,
		Vector3(-10.0f, 9.0f, 20.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		disk_tex);

	butterfly.createButterfly(GL_LINE_LOOP, 10000,
		Vector3(0.0f, 9.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 0.0, 0.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f));

	// blend_cube
	blend_cube.buildFromArray(GL_TRIANGLES,
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

	torus_orbit.buildTorus(GL_TRIANGLES, 2.0, 4.0, 20.0, 10.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, torus edges, tube edges
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(0.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		doughnut_tex);
	// Lighting spheres
	// Sphere to indicate LIGHT0's position
	light_sphere_0.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_1),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);
	// Sphere to indicate LIGHT1's position
	light_sphere_1.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_1),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);
	// Sphere to indicate LIGHT2's position
	light_sphere_2.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_2),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);
	// Sphere to indicate LIGHT3's position
	light_sphere_3.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_3),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 1.0f, 1.0f, 1.0f),
		NULL);
	// Sphere to indicate LIGHT4's position - red
	light_sphere_4.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_4),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(1.0f, 0.0f, 0.0f, 1.0f),
		NULL);
	// Sphere to indicate LIGHT5's position - green
	light_sphere_5.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_5),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(0.0f, 1.0f, 0.0f, 1.0f),
		NULL);
	// Sphere to indicate LIGHT6's position - blue
	light_sphere_6.buildSphere(GL_TRIANGLES, 0.5, 15.0, 15.0,	// radius, latitude, longitude
		Vector3(Light_Position_6),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector4(1.0, 1.0, 1.0, 1.0),
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		NULL);
}

void Scene::renderShapes() {
	//glDisable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
	//
	disc_pres.render();
	torus_pres.render();
	torus_three.render();
	torus_three_1.render();
	cylinder_pres.render();
	sphere_pres.render();
	cone_pres.render();
	butterfly.render2D();
	//glEnable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
	// Lights' spheres
	light_sphere_0.render();
	light_sphere_1.render();
	light_sphere_2.render();
	light_sphere_3.render();
	light_sphere_5.render();
	light_sphere_4.render();
	light_sphere_6.render();
}

void Scene::renderSolarSystem() {
	// SOLAR SYSTEM START //
	glPushMatrix(); { // SUN - start
		glTranslatef(0, 10.0f, 0);										// Move entire solar system (Center of the universe is here)
		glScalef(2.0f, 2.0f, 2.0f);										// Scale entire solar system
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
					glRotatef(angle - 0.3f, 0, 1, 0);				// planet 3 rotation

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
			glRotatef(-angle * 2.0f, 0, 1, 0);						// orbit 4 rotation

			glPushMatrix(); {										// planet 1 orbit - start
				glRotatef(-angle - 0.2f, 0, 1, 0);					// rotate planet 1 orbit
				glScalef(8.0f, 8.0f, 8.0f);							// scale planet 1 orbit
				circle.render2D();									// render planet 1 orbit
			} glPopMatrix();										// planet 1 orbit - end

			glTranslatef(16.0f, 0, 0);								// translate planet 1 with respect to the sun
			glPushMatrix(); {
				glRotatef(angle, 0, 1, 0);							// planet 1 rotation
				planet_8.render();									// render planet 1
			} glPopMatrix();

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
	// SOLAR SYSTEM END //
}

void Scene::renderFloor() {
	main_floor.render(point,
		biliner,
		mipmapping,
		half_mipmapping,
		half_trilinear,
		trilinear);
}

void Scene::renderLeftWall() {
	glPushMatrix(); {
		glTranslatef(-18.0f, 5.0f, 23.0f);

		//glPushMatrix(); {
		//		glTranslatef(0.0f, 0.0, -4.6f);
		//		cylinder.render();
		//		//glPushMatrix();
		//		glTranslatef(2.3f, 0.0, -3.9f);
		//		cylinder.render();
		//		//glPopMatrix();
		//} glPopMatrix();

		for (float i = 0.0; i <= 46.0f; i += 4.6f) {		// Generate a row of 11 cylidners
			glPushMatrix(); {
				if ((int)i % 2 == 0) {						// if i modulo 2 is 0 - generate cylinder 1
					glTranslatef(0.0, 0.0, -i);
					cylinder_1.render();
				} else {									// else generate cylinder 2
					glTranslatef(0.0, 0.0, -i);
					cylinder_2.render();
				}
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 46.0f; i += 4.6f) {		// Generate a row of 11 cylidners
			glPushMatrix(); {
				if ((int)i % 2 == 0) {						// if i modulo 2 is 0 - generate cylinder 1
					glTranslatef(0.0, 5.0f, -i);
					cylinder_2.render();
				}											// else generate cylinder 2
				else {
					glTranslatef(0.0, 5.0f, -i);
					cylinder_1.render();
				}
			} glPopMatrix();
		}
	} glPopMatrix();
}

void Scene::renderBackWall() {
	glPushMatrix(); {
		glTranslatef(-14.0f, 0.0f, -25.0f);
		glRotatef(-90.0f, 0, 1, 0);

		for (float i = 0.0; i <= 32.0f; i += 4.0f) {		// Generate a row of 9 cones
			glPushMatrix(); {
				glTranslatef(0.0, 0.0, -i);
				glRotatef(-90.0f, 0, 0, 1);
				cone_1.render();
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 28.0f; i += 4.0f) {		// Generate a row of 8 cones
			glPushMatrix(); {
				glTranslatef(-5.0f, 2.0f, -i - 2.0f);
				glRotatef(-90.0f, 0, 0, 1);
				cone_1.render();
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 32.0f; i += 4.0f) {		// Generate a row of 9 cones
			glPushMatrix(); {
				glTranslatef(0.0, 4.0, -i);
				glRotatef(-90.0f, 0, 0, 1);
				cone_2.render();
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 28.0f; i += 4.0f) {		// Generate a row of 8 cones
			glPushMatrix(); {
				glTranslatef(-5.0f, 6.0f, -i - 2.0f);
				glRotatef(-90.0f, 0, 0, 1);
				cone_1.render();
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 32.0f; i += 4.0f) {		// Generate a row of 9 cones
			glPushMatrix(); {
				glTranslatef(0.0, 8.0, -i);
				glRotatef(-90.0f, 0, 0, 1);
				cone_2.render();
			} glPopMatrix();
		}
	} glPopMatrix();
}

void Scene::renderRightWall() {
	glPushMatrix(); {
		glTranslatef(20.0f, 0.0f, -24.0f);
		glRotatef(-90.0f, 0, 1, 0);

		for (float i = 0.0; i <= 48.0f; i += 4.0f) {		// Generate a row of 11 discs
			glPushMatrix(); {
				glTranslatef(i, 0.0, 0.0);
				disc_1.render();
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 48.0f; i += 4.0f) {		// Generate a row of 11 discs
			glPushMatrix(); {
				glTranslatef(i, 4.0f, 0.0);
				disc_2.render();
			} glPopMatrix();
		}

		for (float i = 0.0; i <= 48.0f; i += 4.0f) {		// Generate a row of 11 discs
			glPushMatrix(); {
				glTranslatef(i, 8.0f, 0.0);
				disc_3.render();
			} glPopMatrix();
		}
	} glPopMatrix();
}

void Scene::renderPlanets() {
	glDisable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
	glPushMatrix(); {
		glTranslatef(-3.0f, 1.0f, 0.0f);
		glScalef(2.0f, 2.0f, 2.0f);
		glRotatef(90, 0, 1, 0);

		sphere_1.render();
		sphere_2.render();
		sphere_3.render();
		sphere_4.render();
		sphere_5.render();
		sphere_6.render();
		sphere_7.render();
		sphere_8.render();
	} glPopMatrix();
	torus_1.render();
	torus_2.render();
	torus_3.render();
	glEnable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled
}

void Scene::setMaterials() {
	//// 5x5 sphere
	sphere_1.set_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	sphere_1.set_diffuse(0.8f, 0.8f, 0.8f, 0.8f);
	sphere_1.set_specular(0.75f, 0.75f, 0.75f, 1.0f);
	sphere_7.set_emission(0.0f, 0.0f, 0.0f, 1.0f);
	sphere_1.set_shininess(0.0f);
	// 10x10 sphere
	sphere_2.set_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	sphere_2.set_diffuse(0.8f, 0.8f, 0.8f, 0.8f);
	sphere_2.set_specular(0.0f, 0.0f, 1.0f, 1.0f);
	sphere_2.set_emission(0.0f, 0.0f, 1.0f, 1.0f);
	sphere_2.set_shininess(16.0f);
	// 15x15 sphere - Diffuse material only *No ambient or specular
	sphere_3.set_ambient(0.1f, 0.1f, 0.1f, 1.0f);
	sphere_3.set_diffuse(0.6f, 0.6f, 0.6f, 1.0f);
	//sphere_3.set_shininess(32.0f);
	// 15x10 sphere - Diffuse and specular material/reflection + low shininess *Noambient *Shininess of 50
	sphere_4.set_ambient(0.1f, 0.1f, 0.1f, 1.0f);
	sphere_4.set_diffuse(0.6f, 0.6f, 0.6f, 1.0f);
	sphere_4.set_shininess(50.0f);
	// 30x30 sphere Diffuse and specular material/reflection + high shininess *No ambient *Shininess set to 128
	sphere_5.set_ambient(0.0f, 0.0f, 0.0f, 1.0f);
	sphere_5.set_diffuse(0.0f, 0.0f, 0.0f, 0.0f);
	sphere_5.set_specular(0.75f, 0.75f, 0.75f, 1.0f);
	sphere_5.set_shininess(128.0f);
	// 45x30 Diffuse and emission materials *Emission set to a low blue *No ambient or specular
	sphere_6.set_ambient(  0.2f, 0.2f, 0.2f, 1.0f);
	sphere_6.set_diffuse(  0.8f, 0.8f, 0.8f, 1.0f);
	sphere_6.set_specular( 0.0f, 0.0f, 0.0f, 1.0f);
	sphere_6.set_emission( 0.0f, 0.0f, 0.5f, 1.0f);
	//sphere_6.set_shininess(80.0f);
	// 80x80 sphere
	sphere_7.set_ambient(  0.2f, 0.2f, 0.2f, 1.0f);
	sphere_7.set_diffuse(  0.8f, 0.8f, 0.8f, 1.0f);
	sphere_7.set_specular( 0.0f, 0.0f, 0.0f, 1.0f);
	sphere_7.set_emission( 0.0f, 0.5f, 0.5f, 1.0f);
	sphere_7.set_shininess(80.0f);

	// 160x160 sphere
	sphere_8.set_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	sphere_8.set_diffuse(0.8f, 0.8f, 0.8f, 1.0f);
	sphere_8.set_specular(0.75f, 0.75f, 0.75f, 1.0f);
	sphere_8.set_shininess(112.0f);
}

void Scene::buildLight() {
	// Light 0 - spot light in -y direction and 45.0 degree cut off
	light_0_position.set(0.0f, 1.0f, 0.0f, 1.0f);
	Vector4 ambient_0(0.2f, 0.2f, 0.2f, 1.0f);
	Vector4 diffuse_0(0.8f, 0.8f, 0.8f, 1.0f);
	Vector4 specular_0(0.2f, 0.2f, 0.2f, 1.0f);
	Vector3 spot_direction_0(0.0f, -1.0f, 0.0f);

	setLightPosition(light_0_position, Light_Position_0);
	setLightAmbient(ambient_0, Light_Ambient_0);
	setLightDiffuse(diffuse_0, Light_Diffuse_0);						// Light colour
	setLightSpecular(specular_0, Light_Specular_0);
	setSpotDirection(spot_direction_0, Light_Spot_Direction_0);
	setLightCutOff(45.0f, Light_Cut_Off_0);
	// Light 1 - directional light in positive x direction
	light_1_position.set(-1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 ambient_1(0.2f, 0.2f, 0.2f, 1.0f);
	Vector4 diffuse_1(0.8f, 0.8f, 0.8f, 1.0f);
	Vector4 specular_1(0.3f, 0.3f, 0.3f, 1.0f);
	//Vector3 spot_direction_1(1.0f, 0.0f, 0.0f);

	setLightPosition(light_1_position, Light_Position_1);
	setLightAmbient(ambient_1, Light_Ambient_1);
	setLightDiffuse(diffuse_1, Light_Diffuse_1);						// Light colour
	setLightSpecular(specular_1, Light_Specular_1);
	//setSpotDirection(spot_direction_1, Light_Spot_Direction_1);
	//setLightCutOff(180.0f, Light_Cut_Off_1);
	// Light 2 - low attenuation light
	light_2_position.set(0.0f, 5.0f, 0.0f, 1.0f);
	Vector4 ambient_2(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 diffuse_2(0.6f, 0.6f, 0.6f, 1.0f);
	Vector4 specular_2(0.0f, 1.0f, 0.0f, 1.0f);
	//Vector3 direction_2(0.0f, -1.0f, 0.0f);

	setLightPosition(light_2_position, Light_Position_2);
	setLightAmbient(ambient_2, Light_Ambient_2);
	setLightDiffuse(diffuse_2, Light_Diffuse_2);						// Light colour
	setLightSpecular(specular_2, Light_Specular_2);
	// Light 3 - point light
	light_3_position.set(0.0f, 5.0f, 0.0f, 1.0f);
	Vector4 ambient_3(0.8f, 0.8f, 0.8f, 1.0f);
	Vector4 diffuse_3(0.6f, 0.6f, 0.6f, 1.0f);
	Vector4 specular_3(1.0f, 1.0f, 1.0f, 1.0f);

	setLightPosition(light_3_position, Light_Position_3);
	setLightAmbient(ambient_3, Light_Ambient_3);
	setLightDiffuse(diffuse_3, Light_Diffuse_3);						// Light colour
	setLightSpecular(specular_3, Light_Specular_3);

	// Light 4 - point light - medium attenuation - red colour
	light_4_position.set(0.0f, 7.0f, 0.0f, 1.0f);
	Vector4 ambient_4(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 diffuse_4(1.0f, 0.0f, 0.0f, 1.0f);
	Vector4 specular_4(1.0f, 0.0f, 0.0f, 1.0f);

	setLightPosition(light_4_position, Light_Position_4);
	setLightAmbient(ambient_4, Light_Ambient_4);
	setLightDiffuse(diffuse_4, Light_Diffuse_4);						// Light colour
	setLightSpecular(specular_4, Light_Specular_4);
	// Light 5 - point light - medium attenuation - green colour
	light_5_position.set(0.0f, 9.0f, 0.0f, 1.0f);
	Vector4 ambient_5(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 diffuse_5(0.0f, 1.0f, 0.0f, 1.0f);							// Light colour
	Vector4 specular_5(0.0f, 1.0f, 0.0f, 1.0f);

	setLightPosition(light_5_position, Light_Position_5);
	setLightAmbient(ambient_5, Light_Ambient_5);
	setLightDiffuse(diffuse_5, Light_Diffuse_5);						// Light colour
	setLightSpecular(specular_5, Light_Specular_5);
	// Light 6 - point light - medium attenuation - blue colour
	light_6_position.set(13.0f, 4.0f, 0.0f, 1.0f);
	Vector4 ambient_6(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4 diffuse_6(0.0f, 0.0f, 1.0f, 1.0f);
	Vector4 specular_6(0.0f, 0.0f, 1.0f, 1.0f);

	setLightPosition(light_6_position, Light_Position_6);
	setLightAmbient(ambient_6, Light_Ambient_6);
	setLightDiffuse(diffuse_6, Light_Diffuse_6);						// Light colour
	setLightSpecular(specular_6, Light_Specular_6);
}

void Scene::renderLight() {
	// Light 0 - spot light in -y direction and 45.0 degree cut off - the lowest specular
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position_0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular_0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light_Spot_Direction_0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, Light_Cut_Off_0);
	if (light_0) { glEnable(GL_LIGHT0); }									// Enable Light 0
	else glDisable(GL_LIGHT0);

	// Light 1 - directional light in positive x direction - lower specular
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position_1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular_1);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Light_Spot_Direction_1);
	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, Light_Cut_Off_1);
	if (light_1) { glEnable(GL_LIGHT1); }									// Enable Light 1
	else glDisable(GL_LIGHT1);

	// Light 2 - low attenuation light - high specular
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position_2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient_2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse_2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light_Specular_2);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);						// Light 2 attenuation - only a short distance away will receive little or no light from this source
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.25f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.15f);
	if (light_2) { glEnable(GL_LIGHT2); }									// Enable Light 2
	else glDisable(GL_LIGHT2);

	// Light 3 - point light
	glLightfv(GL_LIGHT3, GL_POSITION, Light_Position_3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, Light_Ambient_3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Light_Diffuse_3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Light_Specular_3);
	if (light_3) { glEnable(GL_LIGHT3); }									// Enable Light 3
	else glDisable(GL_LIGHT3);

	// Light 4 - medium attenuation light - red colour
		glLightfv(GL_LIGHT4, GL_POSITION, Light_Position_4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, Light_Ambient_4);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse_4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Light_Specular_4);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0f);						// Light 4 attenuation - medium distance away will receive little or no light from this source
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.25f);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.15f);
	if (light_4) { glEnable(GL_LIGHT4); }									// Enable Light 4
	else glDisable(GL_LIGHT4);

	// Light 5 - medium attenuation light - blue colour
	glLightfv(GL_LIGHT5, GL_POSITION, Light_Position_5);
	glLightfv(GL_LIGHT5, GL_AMBIENT, Light_Ambient_5);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Light_Diffuse_5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Light_Specular_5);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0f);						// Light 5 attenuation - medium distance away will receive little or no light from this source
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.25f);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.15f);
	if (light_5) { glEnable(GL_LIGHT5); }									// Enable Light 5
	else glDisable(GL_LIGHT5);
	// Light 6 - medium attenuation light - blue colour
	glLightfv(GL_LIGHT6, GL_POSITION, Light_Position_6);
	glLightfv(GL_LIGHT6, GL_AMBIENT, Light_Ambient_6);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, Light_Diffuse_6);
	glLightfv(GL_LIGHT6, GL_SPECULAR, Light_Specular_6);
	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0.0f);						// Light 6 attenuation - medium distance away will receive little or no light from this source
	glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.10f);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.05f);
	glEnable(GL_LIGHT6);
	//if (light_6) { glEnable(GL_LIGHT5); }									// Enable Light 6
	//else glDisable(GL_LIGHT5);
}

void Scene::updateVariables() {
	angle += 0.7f;
	/*floor.rotate(angle);
	floor.rotation.setZ(1);
	floor.rotation.setX(1);
	floor.scale.setX(10);
	floor.translate.setX(1);*/
	torus_pres.rotate(angle * 0.5f);
	torus_three.rotate(angle * 0.5f);
	torus_three_1.rotate(-angle * 0.5f);
	blend_cube.rotate(angle);
	disc_pres.rotate(angle);
	cylinder_pres.rotate(angle);
	sphere_pres.rotate(angle);
	cone_pres.rotate(angle);
	//butterfly.rotate(angle);
	// Left wall rotation
	cylinder_1.rotate(angle);
	cylinder_2.rotate(-angle);
	// Back wall rotation
	cone_1.rotate(angle);
	cone_2.rotate(-angle);
	// Right wall rotation
	disc_1.rotate(angle);
	disc_2.rotate(-angle);
	disc_3.rotate(angle * 0.2f);
	//skybox.rotate(angle);
	sphere_1.rotate(angle);
	sphere_2.rotate(angle);
	sphere_3.rotate(angle);
	sphere_4.rotate(angle);
	sphere_5.rotate(angle);
	sphere_6.rotate(angle);
	sphere_7.rotate(angle);
	sphere_8.rotate(angle);
	// Light spheres settings
	// Light 0
	setLightPosition(light_0_position, Light_Position_0);		// Set LIGHT_0 position through amendable varaibles
	light_sphere_0._translate = Light_Position_0;				// Translate light_shpere_0 object into LIGHT_0's position
	// Light 1
	setLightPosition(light_1_position, Light_Position_1);		// Set LIGHT_1 position through amendable varaibles
	light_sphere_1._translate = Light_Position_1;				// Translate light_shpere_1 object into LIGHT_1's position
	// Light 2
	setLightPosition(light_2_position, Light_Position_2);		// Set LIGHT_2 position through amendable varaibles
	light_sphere_2._translate = Light_Position_2;				// Translate light_shpere_2 object into LIGHT_2's position
	// Light 3
	setLightPosition(light_3_position, Light_Position_3);		// Set LIGHT_3 position through amendable varaibles
	light_sphere_3._translate = Light_Position_3;				// Translate light_shpere_3 object into LIGHT_3's position
	// Light 4
	setLightPosition(light_4_position, Light_Position_4);		// Set LIGHT_4 position through amendable varaibles
	light_sphere_4._translate = Light_Position_4;				// Translate light_shpere_4 object into LIGHT_4's position
	// Light 5
	setLightPosition(light_5_position, Light_Position_5);		// Set LIGHT_5 position through amendable varaibles
	light_sphere_5._translate = Light_Position_5;				// Translate light_shpere_5 object into LIGHT_5's position
	// Light 6
	// animate light 6
	if (right) {
		light_6_position.x += 0.1f;
		if (light_6_position.x >= 16.0f) right = false;
	}
	else {
		light_6_position.x -= 0.1f;
		if (light_6_position.x <= -16.0f) right = true;
	}
	setLightPosition(light_6_position, Light_Position_6);		// Set LIGHT_6 position through amendable varaibles
	light_sphere_6._translate = Light_Position_6;				// Translate light_shpere_6 object into LIGHT_6's position
	//setLightSpecular(specular, specular, specular, specular, Light_Specular_1);
	// Butterfly lepring
	if (right) {
		butterfly._translate.y += 0.1f;
		if (butterfly._translate.y >= 16.0f) {
			right = false;
			//butterfly._scale.y *= -1.0f;
		}
	}
	else {
		butterfly._translate.y -= 0.1f;
		if (butterfly._translate.y <= -16.0f) {
			right = true;
			//butterfly._scale.y *= -1.0f;
		}
	}
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
	if (input->isKeyDown(32)) { // 32 - ASCII code for spacebar, (13 - enter)
		scale_x -= 0.1f;
		scale_z -= 0.1f;
	}
	// Texture filtering on/off
	// Toggle Point Sampling
	if (input->isSpecialKeyDown(GLUT_KEY_F7)) {
		point = !point;
		input->SetSpecialKeyUp(GLUT_KEY_F7);
	}
	// Toggle Bilinear Filtering
	if (input->isSpecialKeyDown(GLUT_KEY_F8)) {
		biliner = !biliner;
		input->SetSpecialKeyUp(GLUT_KEY_F8);
	}
	// Toggle Mipmapping Filtering
	if (input->isSpecialKeyDown(GLUT_KEY_F9)) {
		mipmapping = !mipmapping;
		input->SetSpecialKeyUp(GLUT_KEY_F9);
	}
	// Toggle Half Mipmapping Filtering
	if (input->isSpecialKeyDown(GLUT_KEY_F10)) {
		half_mipmapping = !half_mipmapping;
		input->SetSpecialKeyUp(GLUT_KEY_F10);
	}
	// Toggle Half Trilinear Filtering
	if (input->isSpecialKeyDown(GLUT_KEY_F11)) {
		half_trilinear = !half_trilinear;
		input->SetSpecialKeyUp(GLUT_KEY_F11);
	}
	// Toggle Trilinear Filtering
	if (input->isSpecialKeyDown(GLUT_KEY_F12)) {
		trilinear = !trilinear;
		input->SetSpecialKeyUp(GLUT_KEY_F12);
	}
	// Turn lights on/off
	// Toggle light 0 on/off
	if (input->isSpecialKeyDown(GLUT_KEY_F1)) {
		light_0 = !light_0;
		input->SetSpecialKeyUp(GLUT_KEY_F1);
	}
	// Toggle light 1 on/off
	if (input->isSpecialKeyDown(GLUT_KEY_F2)) {
		light_1 = !light_1;
		input->SetSpecialKeyUp(GLUT_KEY_F2);
	}
	// Toggle light 2 on/off
	if (input->isSpecialKeyDown(GLUT_KEY_F3)) {
		light_2 = !light_2;
		input->SetSpecialKeyUp(GLUT_KEY_F3);
	}
	// Toggle light 3 on/off
	if (input->isSpecialKeyDown(GLUT_KEY_F4)) {
		light_3 = !light_3;
		input->SetSpecialKeyUp(GLUT_KEY_F4);
	}
	// Toggle light 4 on/off
	if (input->isSpecialKeyDown(GLUT_KEY_F5)) {
		light_4 = !light_4;
		input->SetSpecialKeyUp(GLUT_KEY_F5);
	}
	// Toggle light 5 on/off
	if (input->isSpecialKeyDown(GLUT_KEY_F6)) {
		light_5 = !light_5;
		input->SetSpecialKeyUp(GLUT_KEY_F6);
	}
	// Light 0 controlls
	if (light_0) {
		// move light right
		if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			light_0_position.x += 0.1f;
		}
		// move light left
		if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			light_0_position.x -= 0.1f;
		}
		// move light up
		if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
			light_0_position.y += 0.1f;
		}
		// move light down
		if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			light_0_position.y -= 0.1f;
		}
		// move light z towards
		if (input->isKeyDown('g') || input->isKeyDown('G') || input->isSpecialKeyDown(GLUT_KEY_PAGE_UP)) {
			light_0_position.z += 0.1f;
		}
		// move light z inwards
		if (input->isKeyDown('t') || input->isKeyDown('T') || input->isSpecialKeyDown(GLUT_KEY_HOME)) {
			light_0_position.z -= 0.1f;
		}
	}
	// Light 1 controlls
	if (light_1) {
		// move light right
		if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			light_1_position.x += 0.1f;
		}
		// move light left
		if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			light_1_position.x -= 0.1f;
		}
		// move light up
		if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
			light_1_position.y += 0.1f;
		}
		// move light down
		if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			light_1_position.y -= 0.1f;
		}
		// move light z towards
		if (input->isKeyDown('g') || input->isKeyDown('G') || input->isSpecialKeyDown(GLUT_KEY_PAGE_UP)) {
			light_1_position.z += 0.1f;
		}
		// move light z inwards
		if (input->isKeyDown('t') || input->isKeyDown('T') || input->isSpecialKeyDown(GLUT_KEY_HOME)) {
			light_1_position.z -= 0.1f;
		}
	}
	// Light 2 controlls
	if (light_2) {
		// move light right
		if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			light_2_position.x += 0.1f;
		}
		// move light left
		if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			light_2_position.x -= 0.1f;
		}
		// move light up
		if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
			light_2_position.y += 0.1f;
		}
		// move light down
		if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			light_2_position.y -= 0.1f;
		}
		// move light z towards
		if (input->isKeyDown('g') || input->isKeyDown('G') || input->isSpecialKeyDown(GLUT_KEY_PAGE_UP)) {
			light_2_position.z += 0.1f;
		}
		// move light z inwards
		if (input->isKeyDown('t') || input->isKeyDown('T') || input->isSpecialKeyDown(GLUT_KEY_HOME)) {
			light_2_position.z -= 0.1f;
		}
	}
	// Light 3 controlls
	if (light_3) {
		// move light right
		if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			light_3_position.x += 0.1f;
		}
		// move light left
		if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			light_3_position.x -= 0.1f;
		}
		// move light up
		if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
			light_3_position.y += 0.1f;
		}
		// move light down
		if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			light_3_position.y -= 0.1f;
		}
		// move light z towards
		if (input->isKeyDown('g') || input->isKeyDown('G') || input->isSpecialKeyDown(GLUT_KEY_PAGE_UP)) {
			light_3_position.z += 0.1f;
		}
		// move light z inwards
		if (input->isKeyDown('t') || input->isKeyDown('T') || input->isSpecialKeyDown(GLUT_KEY_HOME)) {
			light_3_position.z -= 0.1f;
		}
	}
	// Light 4 controlls
	if (light_4) {
		// move light right
		if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			light_4_position.x += 0.1f;
		}
		// move light left
		if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			light_4_position.x -= 0.1f;
		}
		// move light up
		if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
			light_4_position.y += 0.1f;
		}
		// move light down
		if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			light_4_position.y -= 0.1f;
		}
		// move light z towards
		if (input->isKeyDown('g') || input->isKeyDown('G') || input->isSpecialKeyDown(GLUT_KEY_PAGE_UP)) {
			light_4_position.z += 0.1f;
		}
		// move light z inwards
		if (input->isKeyDown('t') || input->isKeyDown('T') || input->isSpecialKeyDown(GLUT_KEY_HOME)) {
			light_4_position.z -= 0.1f;
		}
	}
	// Light 5 controlls
	if (light_5) {
		// move light right
		if (input->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			light_5_position.x += 0.1f;
		}
		// move light left
		if (input->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			light_5_position.x -= 0.1f;
		}
		// move light up
		if (input->isSpecialKeyDown(GLUT_KEY_UP)) {
			light_5_position.y += 0.1f;
		}
		// move light down
		if (input->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			light_5_position.y -= 0.1f;
		}
		// move light z towards
		if (input->isKeyDown('g') || input->isKeyDown('G') || input->isSpecialKeyDown(GLUT_KEY_PAGE_UP)) {
			light_5_position.z += 0.1f;
		}
		// move light z inwards
		if (input->isKeyDown('t') || input->isKeyDown('T') || input->isSpecialKeyDown(GLUT_KEY_HOME)) {
			light_5_position.z -= 0.1f;
		}
	}
	// Camera input controll
	float mousePositionX(int width);
	float mousePositionY(int height);
	camera->cameraControll(dt, width, height, input);
	// Force mouse to return to the centre of the window
	glutWarpPointer(width / 2, height / 2);
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
	renderShadowing();
	//renderStencilShadowing();
	// Render geometry here -------------------------------------
	// Stencil buffer
	renderStencilBuffer();
	// Blend cube
	setRenderMode(blend, wireframe);
	blend_cube.renderBlend();
	setRenderMode(blend, wireframe);
	// Render shapes
	renderShapes();
	// Solar system
	//renderSolarSystem();
	// Render planets for lighting testing
	renderPlanets();
	// Render floor
	renderFloor();
	// Render walls
	renderLeftWall();
	renderBackWall();
	renderRightWall();
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

void Scene::setLightSpecular(float x, float y, float z, float w, GLfloat* lightSpecular) {
	lightSpecular[0] = x;
	lightSpecular[1] = y;
	lightSpecular[2] = z;
	lightSpecular[3] = w;
}

void Scene::setSpotDirection(float x, float y, float z, GLfloat* spotDirection) {
	spotDirection[0] = x;
	spotDirection[1] = y;
	spotDirection[2] = z;
}
// Setting light with Vector4 and Vector3
void Scene::setLightAmbient(Vector4 ambient, GLfloat* lightAmbient) {
	lightAmbient[0] = ambient.x;
	lightAmbient[1] = ambient.y;
	lightAmbient[2] = ambient.z;
	lightAmbient[3] = ambient.w;
}

void Scene::setLightDiffuse(Vector4 diffuse, GLfloat* lightDiffuse) {
	lightDiffuse[0] = diffuse.x;
	lightDiffuse[1] = diffuse.y;
	lightDiffuse[2] = diffuse.z;
	lightDiffuse[3] = diffuse.w;
}

void Scene::setLightPosition(Vector4 position, GLfloat* lightPosition) {
	lightPosition[0] = position.x;
	lightPosition[1] = position.y;
	lightPosition[2] = position.z;
	lightPosition[3] = position.w;
}

void Scene::setLightSpecular(Vector4 specular, GLfloat* lightSpecular) {
	lightSpecular[0] = specular.x;
	lightSpecular[1] = specular.y;
	lightSpecular[2] = specular.z;
	lightSpecular[3] = specular.w;
}

void Scene::setSpotDirection(Vector3 spot_direction, GLfloat* spotDirection) {
	spotDirection[0] = spot_direction.x;
	spotDirection[1] = spot_direction.y;
	spotDirection[2] = spot_direction.z;
}

void Scene::setLightShininess(GLfloat *arg, GLfloat* lightShininess) {
	lightShininess[0] = arg[0];
}

void Scene::setLightShininess(GLfloat arg, GLfloat* lightShininess) {
	lightShininess[0] = arg;
}

void Scene::setLightCutOff(GLfloat* arg, GLfloat& lightCutOff) {
	lightCutOff = arg[0];
}

void Scene::setLightCutOff(GLfloat arg, GLfloat& lightCutOff) {
	lightCutOff = arg;
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

