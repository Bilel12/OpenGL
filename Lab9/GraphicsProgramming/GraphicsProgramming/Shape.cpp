#include "shape.h"


extern GLubyte indices[]=	{0,   1,   2,	//front
							0,   2,   3,
							};

extern float verts[] = {	-1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
							//1.0, -1.0, 1.0
						};

extern float norms[] = { 0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
 						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
						};		


extern float texcoords[]= {	0.0, 0.0, 		//0
							0.0, 1.0, 		//1
 							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							};

void Shape::render1()
{
	// add code to render the cube (above) using method 1
	glEnableClientState(GL_VERTEX_ARRAY);
	/*glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);*/

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glVertexPointer(3, GL_FLOAT, 0, norms);
	glVertexPointer(2, GL_FLOAT, 0, texcoords);

	glBegin(GL_TRIANGLES); {
		glArrayElement(0);
		glArrayElement(1);
		glArrayElement(2);
	} glEnd();

	glBegin(GL_TRIANGLES); {
		glArrayElement(0);
		glArrayElement(2);
		glArrayElement(3);
	} glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	/*glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);*/

	

}

void Shape::render2()
{
	// add code to render the cube (above) using method 2
	// glDrawArrays()

}

void Shape::render3()
{
	// add code to render the cube (above) using method 3
	// glDrawElements()

}


