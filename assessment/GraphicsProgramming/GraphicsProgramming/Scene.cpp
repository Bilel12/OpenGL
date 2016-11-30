#include "Scene.h"

Scene::Scene(Input *in) {
	// Store pointer for input class
	input = in;
	// Camera
	camera = &freeCamera;
	//OpenGL settings
	glShadeModel(GL_SMOOTH);						// Enable Smooth Shading
	//glShadeModel(GL_FLAT);						// 
	//glClearColor(0.39f, 0.58f, 93.0f, 1.0f);		// Cornflour Blue Background
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			// Black Background
	glClearDepth(1.0f);								// Depth Buffer Setup
	glClearStencil(0);								// Clear Stencil Buffer
	glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do

	// Other OpenGL / render setting should be applied here.			
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Really Nice Perspective Calculations
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	// For a textured object we can control how the final RGB for the rendered pixel is set (combination of texture and geometry colours)
	glEnable(GL_TEXTURE_2D);										// Enable texturing
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);				// Set The Blending Function For Translucency
	glEnable(GL_LIGHTING);											// Enable Lighting
	glEnable(GL_COLOR_MATERIAL);									// Without it all glColor3f() changes are ignored when lighting is enabled

	//glCullFace(GL_BACK);								// Set Culling Face To Back Face
	//glEnable(GL_CULL_FACE);								// Enable Culling
	//glClearColor(0.1f, 1.0f, 0.5f, 1.0f);				// Set Clear Color (Greenish Color)
	// Construct functions
	loadTextures();		// loading textures into vector
	assignTextures();	// assign textures to pointers
	loadModels();		// load 3D models from files
	//loadLists();		// load lists
	buildShapes();		// Generate vertices, normals and texture coordinates vectors
	buildLight();		// Set up all lighting arrays
	// Initialise variables
	scale_x = 0, scale_y = 0, scale_z = 0;
	blend = false;			// Blending on or off
	wireframe = false;		// Wireframe on or off
	development = true;		// Turn on or off text rendering	
	// Shadowing
	//populateExample();
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
	disc_1.render(GL_TRIANGLES, disk_tex);
	glEndList();

	Sphere = glGenLists(2);
	glNewList(Sphere, GL_COMPILE);
	sphere.render(GL_TRIANGLES, globe_tex);
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
	//draw.drawCylinder(2.0, 200.0, 3.0, 0.0, 5.0, -5.0, barrel_tex);
	//draw.drawCylinder(2., 50., 10., 3., 3., 3., disk_tex);
	//draw.drawCylinderTwoTex(2., 10., 20., 3., 3., 3., barrel_lid_1_tex, barrel_side_tex);
	//draw.drawCylinderOneTex(2., 10., 20., 3., 3., 3., barrel_tex);
	//draw.drawSphereTorus(100, scale_x, scale_y, scale_z, 0.23); // frame rate starts droping at rot_interval < 0.13 on MAC < 0.23 on Uni PCs
	//draw.drawIcosahedron();
	//draw.drawIcosahedron();
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
	floor.render(GL_TRIANGLES, 0.5, 0.5, 0.5, 0.5);
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
	floor.render(GL_TRIANGLES, 0.5, 0.5, 0.5, 0.5);						// Draw floor object
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
	generateShadowMatrix(Light_Position_1, quad_shadow.get_verts()->data());
	// Floor for shadowing
	quad_shadow.render(GL_QUADS);
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
	generateShadowMatrix(Light_Position_1, quad_shadow.get_verts()->data());
	// Shadow surface
	quad_shadow.render(GL_QUADS);
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
	floor.render(GL_TRIANGLES, 0.5, 0.5, 0.5, 0.5);						// Draw floor object
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
	sphere.buildSphere(	2.0, 5.0, 35.0,		// radius, latitude, longitude
						1, 1, 1,			// scale x, scale y, scale z
						0, 0, -5,			// translate x, translate y, translate z
						angle, 0, 1, 0 );	// rotation angle, rotation x, rotation y, rotation z
	//sphere.set_ambient(1, 1, 1, 1);
	//sphere.set_diffuse(1, 1, 1, 1);
	sphere.set_ambient(	1.0f, 1.0f, 1.0f, 1.0f);
	sphere.set_diffuse(	1.0f, 1.0f, 1.0f, 1.0f);
	sphere.set_shininess(120.0f);

	sun.buildSphere(	0.5, 15.0, 15.0,	// radius, latitude, longitude
						1, 1, 1,			// scale x, scale y, scale z
						0, 0, 0,			// translate x, translate y, translate z
						0, 0, 0, 0);		// rotation angle, rotation x, rotation y, rotation z

	disc_1.buildDisc(	10, 2,				// edges, radius
						1, 1, 1, 			// scale x, scale y, scale z
						-3, 3, 3, 			// translate x, translate y, translate z
						180, 0, 1, 0);		// rotation angle, rotation x, rotation y, rotation z

	disc_2.buildDisc(	200, 2,				// edges, radius
						1, 1, 1,			// scale x, scale y, scale z,
						3, 3, 3,			// translate x, translate y, translate z,
						180, 0, 1, 0);		// rotation angle, rotation x, rotation y, rotation z

	disc_flat.buildDisc(10, 2,				// edges, radius
						1, 1, 1, 			// scale x, scale y, scale z
						0, 0, 0, 			// translate x, translate y, translate z
						-90, 1, 0, 0);		// rotation angle, rotation x, rotation y, rotation z

	quad_shadow.buildQuadShadow(	1, 1, 1,			// scale x, scale y, scale z
									0, 0.35, 0,			// translate x, translate y, translate z
									0., 0., 0., 0.);		// rotation angle, rotation x, rotation y, rotation z
	quad_shadow.set_ambient(		1.f, 1.f, 1.f, 1.f);
	quad_shadow.set_diffuse(		1.f, 1.f, 1.f, 1.f);
	quad_shadow.set_specular(		1.f, 1.f, 1.f, 1.f);
	quad_shadow.set_shininess(		120.0f );
	quad_shadow.scale.set(			1.5, 1.5, 1.5);

	circle.buildCircle(	50,					// edges, radius
						1, 1, 1, 			// scale x, scale y, scale z
						-5, 0, 0, 			// translate x, translate y, translate z
						0, 1, 1, 1);		// rotation angle, rotation x, rotation y, rotation z

	floor.buildQuad(	1, 1, 1,			// scale x, scale y, scale z
						0, 0, 0,			// translate x, translate y, translate z
						0, 0, 0, 0);		// rotation angle, rotation x, rotation y, rotation z

	cone.buildCone(		2, 10, 10,			// radius, edges, height
						1, 1, 1,			// scale x, scale y, scale z
						5, 5, -10,			// translate x, translate y, translate z
						0, 0, 0, 0);		// rotation angle, rotation x, rotation y, rotation z

	cylinder.buildCylinder(	2.3, 20, 10,	// radius, edges, height
							1, 1, 1,		// scale x, scale y, scale z
							3, 3, 3,		// translate x, translate y, translate z
							180, 0, 0, 1);	// rotation angle, rotation x, rotation y, rotation z
	cylinder.set_ambient(	1, 1, 1, 1);

	torus.buildTorus(	2.0, 4.0, 20.0, 10.0,	// r - radius of the tube, R - distance from the center of the tube to the center of the torus, tube edges, torus edges
						1, 1, 1,				// scale x, scale y, scale z
						3., 7., 3.,				// translate x, translate y, translate z
						0., 0., 0., 0);			// rotation angle, rotation x, rotation y, rotation z
}

void Scene::renderShapes() {
	sphere.render(GL_TRIANGLES, globe_tex);
	disc_1.render(GL_TRIANGLE_FAN, 0.5, 0.0, 0.0, 0.5, disk_tex);
	disc_2.render(GL_TRIANGLE_FAN, disk_tex);
	//disc_flat.render(disk_tex);
	circle.renderCircle();
	cone.render(GL_TRIANGLES, disk_tex);
	cylinder.render(GL_TRIANGLES, barrel_tex);
	sun.render(GL_TRIANGLES);
	torus.render(GL_TRIANGLES, disk_tex);
}

void Scene::updateVariables() {
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
	sun.translate.set(Light_Position_1);
	//sphere.rotate(angle);
}

void Scene::buildLight() {
	// Light 0
	setLightAmbient(1, 1, 1, 1, Light_Ambient_0);
	setLightDiffuse(0.6, 0.6, 0.6, 1, Light_Diffuse_0);			// Light colour
	setLightPosition(0, 3, 0, 1, Light_Position_0);
	setLightSpecular(0.5, 0.5, 0.5, 1.0, Light_Specular_0);
	//setSpotDirection(0.0, 1.0, 0.0, Light_Spot_Direction_0);
	// Light 1
	setLightAmbient(0.2, 0.2, 0.2, 0.2, Light_Ambient_1);
	setLightDiffuse(0.6, 0.6, 0.6, 1, Light_Diffuse_1);			// Light colour
	setLightPosition(0, 4, 0, 1, Light_Position_1);
	setLightSpecular(0.5, 0.5, 0.5, 1.0, Light_Specular_1);
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
	//glEnable(GL_LIGHT0);
	
	// Light 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse_1);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_Specular_1);
	/*glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.125);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);*/
	glEnable(GL_LIGHT1);
	// Light 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Ambient_0);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_Diffuse_0);
	glLightfv(GL_LIGHT2, GL_POSITION, Light_Position_0);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light_Specular_0);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.25);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.15);
	//glEnable(GL_LIGHT2);
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
			skybox.renderSkybox(1.0, 1.0, 0., skybox_tex);
		}
		glEnable(GL_DEPTH_TEST);
	} glPopMatrix();
	// Lighting
	renderLight();
	// Shadowing
	//renderShadowing();
	renderStencilShadowing();
	// Render geometry here -------------------------------------
	// Stencil buffer
	//renderStencilBuffer(spaceship);
	// Blend cube
	setRenderMode(blend, wireframe);
	blend_cube.renderBlendCube(0.0, 0.0, 0.5, 1.0, crate_trans_tex);
	setRenderMode(blend, wireframe);
	// Render shapes
	renderShapes();
	// SHADOW II
	//populateExample();
	//buildShadowVolume(Light_Position_0);
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

// An example of the shadow caster object I used.
// Just a 4 by 4 quad stored in a vertex array.
// Can be used when creating the shadow volume and be rendered to the scene.
// for shadow volume build shadow caster
void Scene::buildExample() {
	casterVerts.reserve(11);

	casterVerts[0] = -2.0f;
	casterVerts[1] = 3.0f;
	casterVerts[2] = -2.0f;

	casterVerts[3] = -2.f;
	casterVerts[4] = 3.f;
	casterVerts[5] = 2.f;

	casterVerts[6] = 2.f;
	casterVerts[7] = 3.f;
	casterVerts[8] = 2.f;

	casterVerts[9] = 2.f;
	casterVerts[10] = 3.f;
	casterVerts[11] = -2.f;

	casterNorms.reserve(11);
	// normals
	casterNorms[0] = 0.f;
	casterNorms[1] = 1.f;
	casterNorms[2] = 0.f;
	casterNorms[3] = 0.f;
	casterNorms[4] = 1.f;
	casterNorms[5] = 0.f;
	casterNorms[6] = 0.f;
	casterNorms[7] = 1.f;
	casterNorms[8] = 0.f;
	casterNorms[9] = 0.f;
	casterNorms[10] = 1.f;
	casterNorms[11] = 0.f;
}

// Builds the shadow volume and stores it in a vector (for rendering via vertex array techniques)
// Vector declared as std::Vector<float> shadowVolume;
// Vertices of the shadow caster are extended to create the volume.
void Scene::buildShadowVolume(float lightPosit[4])
{
	float extrusion = 5.f;

	// Clear previous shadow volume
	shadowVolume.clear();

	//Build new shadow volume

	// Temporary variable for storing newly calculated vertcies
	float vExtended[3];


	// For each vertex of the shadow casting object, find the edge 
	// that it helps define and extrude a quad out from that edge.
	for (int i = 0; i < (sizeof(casterVerts) / sizeof(casterVerts[0])); i += 3)
	{
		// Define the edge we're currently working on extruding...
		int e0 = i;
		int e1 = i + 3;

		// If the edge's second vertex is out of array range, 
		// place it back at 0
		if (e1 >= (sizeof(casterVerts) / sizeof(casterVerts[0])))
		{
			e1 = 0;
		}
		// v0 of our extruded quad will simply use the edge's first 
		// vertex or e0.
		shadowVolume.push_back(casterVerts[e0]);
		shadowVolume.push_back(casterVerts[e0 + 1]);
		shadowVolume.push_back(casterVerts[e0 + 2]);

		// v1 of our quad is created by taking the edge's first 
		// vertex and extending it out by some amount.
		extendVertex(vExtended, lightPosit, casterVerts[e0], casterVerts[e0 + 1], casterVerts[e0 + 2], extrusion);
		shadowVolume.push_back(vExtended[0]);
		shadowVolume.push_back(vExtended[1]);
		shadowVolume.push_back(vExtended[2]);

		// v2 of our quad is created by taking the edge's second 
		// vertex and extending it out by some amount.
		extendVertex(vExtended, lightPosit, casterVerts[e1], casterVerts[e1 + 1], casterVerts[e1 + 2], extrusion);
		shadowVolume.push_back(vExtended[0]);
		shadowVolume.push_back(vExtended[1]);
		shadowVolume.push_back(vExtended[2]);

		// v3 of our extruded quad will simply use the edge's second 
		//// vertex or e1.
		shadowVolume.push_back(casterVerts[e1]);
		shadowVolume.push_back(casterVerts[e1 + 1]);
		shadowVolume.push_back(casterVerts[e1 + 2]);
	}

}

// Calculates new vertex positions based on a light position and provide vertex position.
// Puts new vertex positions in newVert for access by buildShadowVolume() function.
// Builds a vector between light and vertex, then extends along that vector by set extrusion amount.
void Scene::extendVertex(float newVert[3], float lightPosit[4], float x, float y, float z, float ext)
{
	float lightDir[3];

	// Create a vector that points from the light's position to the original vertex.
	lightDir[0] = x - lightPosit[0];
	lightDir[1] = y - lightPosit[1];
	lightDir[2] = z - lightPosit[2];

	// Then use that vector to extend the original vertex out to a new position.
	// The distance to extend or extrude the new vector is specified by t.
	newVert[0] = lightPosit[0] + lightDir[0] * ext;
	newVert[1] = lightPosit[1] + lightDir[1] * ext;
	newVert[2] = lightPosit[2] + lightDir[2] * ext;
}

