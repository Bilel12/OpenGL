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
//#include <GL/glew.h>
//#include <GL/glut.h>
//#include "Input.h"
#include <stdio.h>
#include <vector>
// Further includes should go here:
#include "SOIL.h"
#include "FreeCamera.h"
#include "SecurityCamera.h"
#include "TopDownCamera.h"
#include "Camera.h"
#include "Shape.h"
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
	void drawShapes();
	void setRenderMode(bool blend, bool wireframe);
	void loadModels();
	void renderStencilBuffer(Model model);
	void buildShapes();
	void renderShapes();
	void updateVariables();
	void buildLight();
	void renderLight();
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
	// Models
	Model spaceship;
	Model drone;
	// Shapes
	Shape skybox;
	Shape sphere;
	Shape cone;
	Shape disc_1, disc_2, disc_flat;
	Shape blend_cube;
	Shape floor;
	Shape cylinder;
	Shape circle;
	// Drawn shapes
	Draw draw;
	// Objects for lists creating
	GLuint Torus;
	GLuint Disc;
	GLuint Sphere;
	GLuint LowPoliCylinder;
	GLuint HighPoliCylinder;
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
	// Rotation variables
	float scale_x, scale_y, scale_z;
	float angle;		// Rotate by angle
						// Toggle variables
	bool blend;			// toggle bledning effect
	bool wireframe;		// toggle wireframe mode
	bool development;	// toggle development mode i.e. display text
	// Lighting
	GLfloat highSpec[4];
	GLfloat no_mat[4];
	GLfloat mat_ambient[4];
	GLfloat mat_ambient_colour[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];

	GLfloat shininess[1];
	GLfloat no_shininess[1];
	GLfloat low_shininess[1];
	GLfloat high_shininess[1];

	GLfloat Light_Ambient[4];
	GLfloat Light_Ambient1[4];
	GLfloat Light_Diffuse[4];
	GLfloat Light_Position[4];
	GLfloat Light_Position1[4];
	GLfloat spot_Direction[4];
	GLfloat Light_Specular[4];
	// Set light
	GLfloat* setLightAmbient(float x, float y, float z, float w, GLfloat* lightAmbient);
	GLfloat* setLightDiffuse(float x, float y, float z, float w, GLfloat* lightDiffuse);
	GLfloat* setLightPosition(float x, float y, float z, float w, GLfloat* lightPosition);
	GLfloat* setSpotDirection(float x, float y, float z, float w, GLfloat* spotDirection);
	// Set light Specular
	GLfloat* setLightSpecular(float x, float y, float z, float w, GLfloat* lightSpecular);
	GLfloat* setHighSpec(float x, float y, float z, float w, GLfloat* highSpec);
	GLfloat* set_no_mat(float x, float y, float z, float w, GLfloat* no_mat);
	GLfloat* set_mat_ambient(float x, float y, float z, float w, GLfloat* mat_ambient);
	GLfloat* set_mat_ambient_colour(float x, float y, float z, float w, GLfloat* mat_ambient_colour);
	GLfloat* set_mat_diffuse(float x, float y, float z, float w, GLfloat* mat_diffuse);
	GLfloat* set_mat_specular(float x, float y, float z, float w, GLfloat* mat_specular);
	GLfloat* set_mat_emission(float x, float y, float z, float w, GLfloat* mat_emission);
	// Set variables
	GLfloat* set_shininess(float s, GLfloat* shininess);
	GLfloat* set_no_shininess(float s, GLfloat* no_shininess);
	GLfloat* set_low_shininess(float s, GLfloat* low_shininess);
	GLfloat* set_high_shininess(float s, GLfloat* high_shininess);
	// Shadowing
	std::vector<float> shadowMatrix;
	std::vector<float> shadowVolume;
	std::vector<float> casterVerts;
	std::vector<float> casterNorms;

	void buildShadowVolume(float lightPosit[4]);
	void generateShadowMatrix(float light_pos[4], GLfloat floor[12]);
	void extendVertex(float newVert[3], float lightPosit[4], float x, float y, float z, float ext);
	void populateExample();
};

#endif