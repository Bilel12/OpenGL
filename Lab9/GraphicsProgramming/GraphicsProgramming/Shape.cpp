#include "shape.h"


static GLfloat colors[] = { 1.0, 0.2, 0.2,
							0.2, 0.2, 1.0,
							0.8, 1.0, 0.2,
							0.75, 0.75, 0.75,
							0.35, 0.35, 0.35,
							0.5, 0.5, 0.5 
							};

extern GLubyte indices[]=	{	0,   1,   2,	//front
								0,   2,   3,
							};


extern float verts[] = { 
                         // front face
                         -1, -1, 1,			// Vertex #0
                          1, -1, 1,		// Vertex #1
                          1,  1, 1,		// Vertex #2
                          1,  1, 1,			// Vertex #3
                         -1,  1, 1,
                         -1, -1, 1,
	                     // right side face
	1, -1, 1,
	1, -1, -1,
	1, 1, 1,
	1, 1, 1,
	1, 1, -1,
	1, -1, -1,
	// left side face
						   	-1, -1, -1,
						   -1, 1, -1,
						   	-1, 1, 1,
						   	-1, 1, 1,
						   	-1, -1, 1,
						   -1, -1, -1,
                       };

extern float norms[] = { 
                         // front face
                         0.0, 0.0, 1.0,		//0
                         0.0, 0.0, 1.0,		//1
                         0.0, 0.0, 1.0,		//2
                         0.0, 0.0, 1.0,		//3
                         0.0, 0.0, 1.0,		//3
                         0.0, 0.0, 1.0,		//3
                         0.0, 0.0, 1.0,		//3
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
                       };


extern float texcoords[] = { 
                            // front face
                            0, 1, 		//0
                            1, 1, 		//1
                            1, 0, 		//2
                            1, 0, 		//3
                            0, 0,
                            0, 1,
							// right side face
	0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1,
// left side face
						  
						1, 1,
						 
						 1, 0,
						  0, 0,
						 0, 0,
						  0, 1,
						  1, 1,
                           };

/////////////////////////////
//	///////////////////////////////////
//	glBegin(GL_TRIANGLES); // left side face
//	glColor3f(0, 0, 1);
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1, -1, -1);
//
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(-1, 1, -1);
//
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(-1, 1, 1);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(-1, 1, 1);
//
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(-1, -1, 1);
//
//	glNormal3f(-1.0f, 0.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1, -1, -1);
//	glEnd();
//	//////////////////////////////
//	glBegin(GL_TRIANGLES); // bottom face
//	glColor3f(1, 1, 1);
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1, -1, -1);
//
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(-1, -1, 1);
//
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(1, -1, 1);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(1, -1, 1);
//
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(1, -1, -1);
//
//	glNormal3f(0.0f, -1.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1, -1, -1);
//	glEnd();
//	///////////////////////////////
//	glBegin(GL_TRIANGLES); // back face
//	glColor3f(0, 1, 0); // green
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(-1, -1, -1);
//
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(1, -1, -1);
//
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(1, 1, -1);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(1, 1, -1);
//
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(-1, 1, -1);
//
//	glNormal3f(0.0f, 0.0f, -1.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(-1, -1, -1);
//	glEnd();
//	///////////////////////
//	glBegin(GL_TRIANGLES); // top face
//	glColor3f(0.0, 1.0, 0.0); // green
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(1, 1, 1);
//
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(0, 1);
//	glVertex3f(1, 1, -1);
//
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1, 1, -1);
//	glEnd();
//
//	glBegin(GL_TRIANGLES);
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(1, 1);
//	glVertex3f(-1, 1, -1);
//
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(1, 0);
//	glVertex3f(-1, 1, 1);
//
//	glNormal3f(0.0f, 1.0f, 0.0f);
//	glTexCoord2f(0, 0);
//	glVertex3f(1, 1, 1);
//	glEnd();
//}
//glPopMatrix();





void Shape::render1()
{
	// add code to render the cube (above) using method 1
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glBegin(GL_TRIANGLES);
		for (int i = 0; i < sizeof(indices)/sizeof(indices[0]); ++i) {
		glArrayElement(indices[i]);
	}
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	

}

void Shape::render2()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawArrays(GL_TRIANGLES, 0, 18);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::render3()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}