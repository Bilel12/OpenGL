#ifndef _SKYBOX_H
#define _SKYBOX_H

extern float skybox_verts[] = {
	// front face
	-1, -1, 1,	// Left bottom
	1, -1, 1,	// Right bottom
	1, 1, 1,	// Right top
	1, 1, 1,	// Right top
	-1, 1, 1,	// Left top
	-1, -1, 1,	// Left bottom
				// right side face
	1, -1, 1,	// Right bottom
	1, -1, -1,	// Left bottom
	1, 1, 1,	// Right top
	1, 1, 1,	// Right top
	1, 1, -1,	// Left top
	1, -1, -1,	// Left bottom
				// left side face
	-1, -1, -1,	// Left bottom
	-1, 1, -1,	// Left top
	-1, 1, 1,	// Right top
	-1, 1, 1,	// Right top
	-1, -1, 1,	// Right bottom
	-1, -1, -1,	// Left bottom
	-1, -1, -1,	// Left bottom
	-1, -1, 1,	// Left top
	1, -1, 1,	// Right top
	1, -1, 1,	// Right top
	1, -1, -1,	// Right bottom
	-1, -1, -1,	// Left bottom
				// back face
	-1, -1, -1,	// Left bottom
	1, -1, -1,	// Right bottom
	1, 1, -1,	// Right top
	1, 1, -1,	// Right top
	-1, 1, -1,	// Left top
	-1, -1, -1,	// Left bottom
				// top face
	1, 1, 1,	// Right top
	1, 1, -1,	// Right bottom
	-1, 1, -1,	// Left bottom
	-1, 1, -1,	// Left bottom
	-1, 1, 1,	// Left top
	1, 1, 1,	// Right top
};
extern float skybox_norms[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};
extern float skybox_texcoords[] = {
	// front face
	0.25, 0.5,
	0.5, 0.5,
	0.5, 0.25,
	0.5, 0.25,
	0.25, 0.25,
	0.25, 0.5,
	// right side face
	0.5, 0.5,
	0.75, 0.5,
	0.5, 0.25,
	0.5, 0.25,
	0.75, 0.25,
	0.75, 0.5,
	// left side face
	0, 0.5,
	0, 0.25,
	0.25, 0.25,
	0.25, 0.25,
	0.25, 0.5,
	0, 0.5,
	// bottom face
	0.25, 0.5,
	0.25, 0.75,
	0.5, 0.75,
	0.5, 0.75,
	0.5, 0.5,
	0.25, 0.5,
	// back face
	1, 0.5,
	0.75, 0.5,
	0.75, 0.25,
	0.75, 0.25,
	1, 0.25,
	1, 0.5,
	// top face
	0.5, 0.25,
	0.5, 0,
	0.25, 0,
	0.25, 0,
	0.25, 0.25,
	0.5, 0.25,
};

#endif
