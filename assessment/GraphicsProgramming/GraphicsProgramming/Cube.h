#ifndef _CUBE_H
#define _CUBE_H

static std::vector<float> cube_verts = {
								// front face
								-1.0f, -1.0f, 1.0f,
								1.0f, -1.0f, 1.0f,
								1.0f,  1.0f, 1.0f,
								1.0f,  1.0f, 1.0f,
								-1.0f,  1.0f, 1.0f,
								-1.0f, -1.0f, 1.0f,
								// right side face
								1.0f, -1.0f, 1.0f,
								1.0f, -1.0f, -1.0f,
								1.0f, 1.0f, -1.0f,
								1.0f, 1.0f, -1.0f,
								1.0f, 1.0f, 1.0f,
								1.0f, -1.0f, 1.0f,
								// left side face
								-1.0f, -1.0f, -1.0f,
								-1.0f, -1.0f, 1.0f,
								-1.0f, 1.0f, 1.0f,
								-1.0f, 1.0f, 1.0f,
								-1.0f, 1.0f, -1.0f,
								-1.0f, -1.0f, -1.0f,
								// bottom face
								-1.0f, -1.0f, -1.0f,
								1.0f, -1.0f, -1.0f,
								1.0f, -1.0f, 1.0f,
								1.0f, -1.0f, 1.0f,
								-1.0f, -1.0f, 1.0f,
								-1.0f, -1.0f, -1.0f,
								// back face
								-1.0f, -1.0f, -1.0f,
								-1.0f, 1.0f, -1.0f,
								1.0f, 1.0f, -1.0f,
								1.0f, 1.0f, -1.0f,
								1.0f, -1.0f, -1.0f,
								-1.0f, -1.0f, -1.0f,
								// top face
								1.0f, 1.0f, 1.0f,
								1.0f, 1.0f, -1.0f,
								-1.0f, 1.0f, -1.0f,
								-1.0f, 1.0f, -1.0f,
								-1.0f, 1.0f, 1.0f,
								1.0f, 1.0f, 1.0f,
};
static std::vector<float> cube_norms = {
								// front face
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f,
								0.0f, 0.0f, 1.0f,
								// right side face
								1.0f, 0.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								1.0f, 0.0f, 0.0f,
								1.0f, 0.0f, 0.0f
								// left side face
								-1.0f, 0.0f, 0.0f,
								-1.0f, 0.0f, 0.0f,
								-1.0f, 0.0f, 0.0f,
								-1.0f, 0.0f, 0.0f,
								-1.0f, 0.0f, 0.0f,
								-1.0f, 0.0f, 0.0f,
								// bottom face
								0.0f, -1.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								0.0f, -1.0f, 0.0f,
								// back face
								0.0f, 0.0f, -1.0f,
								0.0f, 0.0f, -1.0f,
								0.0f, 0.0f, -1.0f,
								0.0f, 0.0f, -1.0f,
								0.0f, 0.0f, -1.0f,
								0.0f, 0.0f, -1.0f,
								// top face
								0.0f, 1.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
								0.0f, 1.0f, 0.0f,
};
static std::vector<float> cube_texcoords = {
								// front face
								0, 1,
								1, 1,
								1, 0,
								1, 0,
								0, 0,
								0, 1,
								// right side face
								0, 1,
								1, 1,
								1, 0,
								1, 0,
								0, 0,
								0, 1,
								// left side face
								1, 1,
								0, 1,
								0, 0,
								0, 0,
								1, 0,
								1, 1,
								// bottom face
								1, 1,
								0, 1,
								0, 0,
								0, 0,
								1, 0,
								1, 1,
								// back face
								0, 1,
								0, 0,
								1, 0,
								1, 0,
								1, 1,
								0, 1,
								// top face
								0, 0,
								0, 1,
								1, 1,
								1, 1,
								1, 0,
								0, 0,
};

std::vector<float> quad_t_verts = { -1.0f, -1.0f, -1.0f,
									 1.0f, -1.0f, -1.0f,
									 1.0f, -1.0f,  1.0f,
									 1.0f, -1.0f,  1.0f,
									-1.0f, -1.0f,  1.0f,
									-1.0f, -1.0f, -1.0f };

std::vector<float> quad_verts = {	-1.f, -1.f, -1.f,	//top left
									-1.f, -1.f,  1.f,	// bottom left
									 1.f, -1.f,  1.f,	//bottom right
									 1.f, -1.f, -1.f };	// top right

#endif
