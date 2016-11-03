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
		// bottom face
		
		-1, -1, -1,
		-1, -1, 1,
		1, -1, 1,
		1, -1, 1,
		1, -1, -1,
		-1, -1, -1,
		// back face
		
		-1, -1, -1,
	
		
		1, -1, -1,
	
		
		1, 1, -1,
		
		1, 1, -1,
	
		
		-1, 1, -1,
	
		
		-1, -1, -1,
	///////////////////////
	// top face
1, 1, 1,


1, 1, -1,


-1, 1, -1,

-1, 1, -1,


-1, 1, 1,

1, 1, 1,

	
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
						   // bottom face

					  1, 1,

					  1, 0,

					  0, 0,
					  0, 0,
					  0, 1,
					  1, 1,
						   // back face

						  0, 1,



						  1, 1,



						  1, 0,



						  1, 0,



						  0, 0,



						  0, 1,
						   // top face

						   0, 0,



						   0, 1,



						   1, 1,

						   1, 1,



						   1, 0,

						   0, 0,

					   };

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
						   
						   /////////////////////////////
						  
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
						   /////////////////////////////
					   // front face
					   
					   0.25, 0.5,
					   
					   0.5, 0.5,
					  
					   0.5, 0.25,
					  
					   0.5, 0.25,
					  
					   0.25, 0.25,
					  
					   0.25, 0.5,
					  
					   /////////////////////////////
					   // right side face
					   0.5, 0.5,
					  
					   0.75, 0.5,
					  
					   0.5, 0.25,
					   
					   0.5, 0.25,
					  
					   0.75, 0.25,
					   
					   0.75, 0.5,
					   
					   ///////////////////////////////////
					   // left side face
					  
					   0, 0.5,
					  
					   0, 0.25,
					  
					   0.25, 0.25,
					   
					   0.25, 0.25,
					 
					   0.25, 0.5,
					 
					   0, 0.5,
					  
					   //////////////////////////////
					   // bottom face
					 
					   0.25, 0.5,
					   
					   0.25, 0.75,
					  
					   0.5, 0.75,
					   
					   0.5, 0.75,
					  
					   0.5, 0.5,
					  
					   0.25, 0.5,
					  
					   ///////////////////////////////
					 // back face
					  
					   1, 0.5,
					   
					   0.75, 0.5,
					 
					   0.75, 0.25,
					  
					   0.75, 0.25,
					  
					   1, 0.25,
					  
					   1, 0.5,
					  
					   ///////////////////////
					 // top face
					  
					   0.5, 0.25,
					  
					   0.5, 0,
					  
					   0.25, 0,
					  
					   0.25, 0,
					  
					   0.25, 0.25,
					  
					   0.5, 0.25,
					   };

void Shape::render1()
{
	// add code to render the cube (above) using method 1
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
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
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	

}

void Shape::render2()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::render3()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::render_skybox() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, skybox_verts);
	glNormalPointer(GL_FLOAT, 0, skybox_norms);
	glTexCoordPointer(2, GL_FLOAT, 0, skybox_texcoords);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	return;
}