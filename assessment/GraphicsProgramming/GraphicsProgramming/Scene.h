// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene),
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include <Windows.h>
#include "glew.h"
#include "glut.h"
#include <gl/GLU.h>
#include <gl/GL.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include <vector>
#include "SOIL.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "SecurityCamera.h"
#include "TopDownCamera.h"
#include "Shape.h"
#include "Cube.h"
#include "Skybox.h"
#include "Draw.h"
#include "Model.h"

class Scene {
public:
	Scene(Input *in);
	// Main render function
	void render();
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	Vector3 a;
	Vector3 b;
protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	// Functions
	void loadTextures();
	void assignTextures();
	void loadLists();
	void renderLists();
	void setRenderMode(bool blend, bool wireframe);
	void loadModels();
	void renderStencilBuffer(Model model);
	void renderShadowing();
	void renderStencilShadowing();
	void buildShapes();
	void renderShapes();
	void updateVariables();
	void buildLight();
	void renderLight();
	// rendering textured objects
	void renderSolarSystem();
	void renderFloor();
	void renderWalls();
	void renderPlanets();
	// For Window and frustum calculation.
	int width, height;
	// For FPS counter and mouse coordinate output.
	int frame, time, timebase;
	char fps[40];
	char mouseText[60];
	char cameraPositionText[60];
	char cameraVectorText[60];
	char cameraLookAtText[60];
	char cameraUpText[60];
	char cameraSideText[60];
	char cameraRotationText[60];
	float fov, nearPlane, farPlane;

	// For access to user input.
	Input* input;
	// Cameras
	Camera *camera;
	FreeCamera freeCamera;
	SecurityCamera securityCamera;
	TopDownCamera topDownCamera;
	//FPPCamera fppCamera;
	// Variables for loading textures
	std::vector<GLuint> textures;
	GLuint myTexture;
	// Textures' pointers
	GLuint *crate_tex;
	GLuint *tileBrown_tex;
	GLuint *triangle_tex;
	GLuint *checked_tex;
	GLuint *grass_tex;
	GLuint *glass_tex;
	GLuint *aTrans_tex;
	GLuint *crate_trans_tex;
	GLuint *skybox_tex;
	GLuint *crateArrow_tex;
	GLuint *disk_tex;
	GLuint *barrel_side_tex;
	GLuint *barrel_lid_1_tex;
	GLuint *barrel_lid_2_tex;
	GLuint *globe_tex;
	GLuint *spaceship_tex;
	GLuint *barrel_tex;
	GLuint *doughnut_tex;
	GLuint *earth_clouds_tex;
	GLuint *earth_night_tex;
	GLuint *earth_surface_tex;
	GLuint *jupiter_tex;
	GLuint *mars_tex;
	GLuint *mercury_tex;
	GLuint *moon_tex;
	GLuint *neptune_tex;
	GLuint *saturn_tex;
	GLuint *sun_tex;
	GLuint *venus_atmosphere_tex;
	GLuint *venus_surface_tex;
	// Shapes
	Shape skybox;
	Shape sphere;
	Shape cone;
	Shape disc_1, disc_2, disc_flat;
	Shape blend_cube;
	Shape floor;
	Shape cylinder;
	Shape circle;
	Shape quad;
	Shape light_sphere_0;
	Shape light_sphere_1;
	Shape light_sphere_2;
	Shape torus_orbit;
	Shape torus;
	Shape ico;
	Shape butterfly;
	Shape sun;
	Shape planet_1;
	Shape planet_2;
	Shape planet_3;
	Shape planet_4;
	Shape planet_5;
	Shape planet_6;
	Shape planet_7;
	Shape planet_8;
	// Models
	Model spaceship;
	Model drone;
	// Objects for lists creating
	GLuint Torus;
	GLuint Disc;
	GLuint Sphere;
	GLuint LowPoliCylinder;
	GLuint HighPoliCylinder;
	GLuint Floor;
	// Rotation variables
	float scale_x;
	float scale_y;
	float scale_z;
	float angle;		// Rotate by angle
	// Lights' positions
	Vector4 light_0_position;
	Vector4 light_1_position;
	Vector4 light_2_position;
	// Toggling variables
	bool blend;			// toggle bledning effect
	bool wireframe;		// toggle wireframe mode
	bool development;	// toggle development mode i.e. display text
	bool light_0;
	bool light_1;
	bool light_2;
	//enum light {light_0, light_1, light_2};
	// Lighting
	// Light 0
	GLfloat Light_Ambient_0[4];
	GLfloat Light_Diffuse_0[4];
	GLfloat Light_Position_0[4];
	GLfloat Light_Specular_0[4];
	GLfloat Light_Spot_Direction_0[3];
	// Light 1
	GLfloat Light_Ambient_1[4];
	GLfloat Light_Diffuse_1[4];
	GLfloat Light_Position_1[4];
	GLfloat Light_Specular_1[4];
	GLfloat Light_Spot_Direction_1[3];
	// Light 2
	GLfloat Light_Ambient_2[4];
	GLfloat Light_Diffuse_2[4];
	GLfloat Light_Position_2[4];
	GLfloat Light_Specular_2[4];
	GLfloat Light_Spot_Direction_2[3];
	// Material arrays
	GLfloat no_mat[4]				= { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_ambient[4]			= { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_ambient_colour[4]	= { 0.8f, 0.8f, 0.2f, 1.0f };

	GLfloat mat_diffuse[4]			= { 0.1f, 0.5f, 0.8f, 1.0f };

	GLfloat mat_specular[4]			= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_emission[4]			= { 0.3f, 0.2f, 0.2f, 0.0f };

	GLfloat no_shininess[1]			= { 0.0 };
	GLfloat low_shininess[1]		= { 50 };
	GLfloat high_shininess[1]		= { 100 };

	GLfloat spot_cutoff[1]			= { 180 };
	// Set light
	void setLightAmbient(float x, float y, float z, float w, GLfloat* lightAmbient);	// Set light's ambient
	void setLightDiffuse(float x, float y, float z, float w, GLfloat* lightDiffuse);	// Set light's diffuse
	void setLightPosition(float x, float y, float z, float w, GLfloat* lightPosition);	// Set light's position
	void setSpotDirection(float x, float y, float z, GLfloat* spotDirection);			// Set light's direction
	void setLightSpecular(float x, float y, float z, float w, GLfloat* lightSpecular);	// Set light's specular
	// Set light using Vector4 and Vector3
	void setLightAmbient(Vector4 ambient, GLfloat* lightAmbient);						// Set light's ambient
	void setLightDiffuse(Vector4 diffuse, GLfloat* lightDiffuse);						// Set light's diffuse
	void setLightPosition(Vector4 position, GLfloat* lightPosition);					// Set light's position
	void setLightSpecular(Vector4 specular, GLfloat* lightSpecular);					// Set light's specular
	void setSpotDirection(Vector3 spot_direction, GLfloat* spotDirection);				// Set light's direction

	void setLightShininess(GLfloat *arg, GLfloat* lightShininess);
	void setLightShininess(GLfloat arg, GLfloat* lightShininess);
	// Shadowing
	GLfloat shadowMatrix[16];
	std::vector<float> shadowVolume;
	void generateShadowMatrix(float light_pos[4], GLfloat floor[12]);
};

#endif