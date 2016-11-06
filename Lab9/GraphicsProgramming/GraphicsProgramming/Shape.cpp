#include "Skybox.h"
#include "Cube.h"
#include "Icosahedron.h"
#include "Shape.h"

extern GLubyte indices[] = {
							0,   1,   2,	//front
							0,   2,   3,
							};

extern GLfloat colors[] = { 1.0, 0.2, 0.2,
							0.2, 0.2, 1.0,
							0.8, 1.0, 0.2,
							0.75, 0.75, 0.75,
							0.35, 0.35, 0.35,
							0.5, 0.5, 0.5
							};

void Shape::render1() {
	// add code to render the cube (above) using method 1
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, cube_verts);
	glNormalPointer(GL_FLOAT, 0, cube_norms);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texcoords);

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

void Shape::render3() {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, cube_verts);
	glNormalPointer(GL_FLOAT, 0, cube_norms);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texcoords);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::drawCube() {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, cube_verts);
	glNormalPointer(GL_FLOAT, 0, cube_norms);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texcoords);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::drawSkybox() {
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
}

void Shape::drawTorus(int numc, int numt) {
	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * (double)M_PI;
	for (i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (1 + .1*cos(s*twopi / numc))*cos(t*twopi / numt);
				y = (1 + .1*cos(s*twopi / numc))*sin(t*twopi / numt);
				z = .1 * sin(s * twopi / numc);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

void Shape::drawCircle(int edges) {
	// version I
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < edges; i++)
		glVertex2f(cos((2 * M_PI*i) / edges), sin((2 * M_PI*i) / edges));
	glEnd();
	// version II
	/*glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= edges; i++) {
		if (i == edges) glVertex2f(cos(0), sin(0));
		else glVertex2f(cos((2 * M_PI*i) / edges), sin((2 * M_PI*i) / edges));
	}
	glEnd();*/
}

void Shape::normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		return;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
}

void Shape::normcrossprod(float v1[3], float v2[3], float out[3]){
	GLint i, j;
	GLfloat length;

	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
	normalize(out);
}

void Shape::drawIcosahedron() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++) {
		float d1[3], d2[3], norm[3];
		for (int j = 0; j < 3; j++) {
			d1[j] = vdata[tindices[i][0]][j] - vdata[tindices[i][1]][j];
			d2[j] = vdata[tindices[i][1]][j] - vdata[tindices[i][2]][j];
		}

		normcrossprod(d1, d2, norm);
		glNormal3fv(norm);
		glVertex3fv(&vdata[tindices[i][0]][0]);
		glVertex3fv(&vdata[tindices[i][1]][0]);
		glVertex3fv(&vdata[tindices[i][2]][0]);
	}
	glEnd();
}

void Shape::drawDisc(int edges, float radius, float h, float k) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;
	for (int i = 0; i < edges; ++i) {
		glBegin(GL_TRIANGLE_FAN);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(h + start, k + start, start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta), k + radius * sin(theta), start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta + interval), k + radius * sin(theta + interval), start);
		glEnd();
		theta += interval;
	}
}

void Shape::drawFlatDisc(int edges, float radius, float h, float k) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;
	for (int i = 0; i < edges; ++i) {
		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(start + 0.5, start + 0.5);
		glVertex3f(h + start, start, k + start);

		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
		glVertex3f(h + radius * cos(theta), start, k + radius * sin(theta));

		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
		glVertex3f(h + radius * cos(theta + interval), start, k + radius * sin(theta + interval));
		glEnd();
		theta += interval;
	}
}

void Shape::drawSphere(float radius, int lats, int longs, float h, float k) {
	//float theta = (2.0 * M_PI) / lats; // angle of latitude
	//float delta = M_PI / longs;	// angle of longitude

	//for (int i = 0; i < longs; ++i) {
	//	for (int j = 0; j < lats; ++j) {
	//		float x = radius *cos(theta) * sin(delta);
	//		float y = radius * cos(delta);
	//		float z = radius * sin(theta) * sin(delta);
	//		glBegin(GL_QUAD_STRIP);
	//			glNormal3f( radius *cos(theta) * sin(delta),				radius * cos(delta),			radius * sin(theta) * sin(delta));
	//			glVertex3f(	radius *cos(theta) * sin(delta),				radius * cos(delta),			radius * sin(theta) * sin(delta));

	//			glNormal3f( radius *cos(theta) * sin(delta),				radius * cos(delta) + j,		radius * sin(theta) * sin(delta));
	//			glVertex3f(	radius *cos(theta) * sin(delta),				radius * cos(delta) + j,		radius * sin(theta) * sin(delta));

	//			glNormal3f( radius *cos(theta) * sin(delta) + i,			radius * cos(delta) + j,		radius * sin(theta) * sin(delta));
	//			glVertex3f(	radius *cos(theta) * sin(delta) + i,			radius * cos(delta) + j,		radius * sin(theta) * sin(delta));

	//			glNormal3f( radius *cos(theta) * sin(delta) + i,			radius * cos(delta),			radius * sin(theta) * sin(delta));
	//			glVertex3f(	radius *cos(theta) * sin(delta) + i,			radius * cos(delta),			radius * sin(theta) * sin(delta));
	//		glEnd();
	//	}
	//}
	
	for (int i = 0; i <= lats; i++) {
		float theta = M_PI * (-0.5 + (float)(i - 1) / lats);
		float z0 = sin(theta);
		float zr0 = cos(theta);

		float delta = M_PI * (-0.5 + (float)i / lats);
		float z1 = sin(delta);
		float zr1 = cos(delta);

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= longs; j++) {
			float lng = 2 * M_PI * (float)(j - 1) / longs;
			float x = cos(lng);
			float y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}

void Shape::drawCylinder(float radius, float edges, float stacks, float h, float k) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;

	for (int i = 0; i < edges; ++i) {
		glBegin(GL_TRIANGLE_STRIP); {
			// top
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(h + start, k + start, start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta), k + radius * sin(theta), start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta + interval), k + radius * sin(theta + interval), start);
			// bottom
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(-h + start, -k + start, start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(-h + radius * cos(theta), -k + radius * sin(theta), start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(-h + radius * cos(theta + interval), -k + radius * sin(theta + interval), start);
		} glEnd();
		theta += interval;
	}

	////float theta = ((float)i) * 2.0 * M_PI;
	////float nextTheta = ((float)i + 1) * 2.0 * M_PI;
	//for (int i = 0; i < edges; i++) {
	//	glBegin(GL_TRIANGLE_STRIP);
	//	glVertex3f(start, h, start); //vertex at middle of end
	//	glVertex3f(radius * cos(theta),			 h,		radius * sin(theta)); //vertices at edges of circle*
	//	glVertex3f(radius * cos(theta),		 h + 1,		radius * sin(theta));
	//	// the same vertices at the bottom of the cylinder
	//	glVertex3f(radius * cos(nextTheta),		-h,		radius * sin(nextTheta));
	//	glVertex3f(radius * cos(theta),			-h + 1,		radius * sin(theta));
	//	glVertex3f(start, -h, start);
	//	glEnd();
	//	theta += interval;
	//}
}

void Shape::drawFlatCylinder(float radius, float edges, float stacks, float h, float k) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;

	//for (int i = 0; i < edges; ++i) {
	//	glBegin(GL_TRIANGLE_STRIP); {
	//		// top
	//		glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(start + 0.5, start + 0.5);
	//		glVertex3f(h + start, start, k + start);

	//		glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
	//		glVertex3f(h + radius * cos(theta), start, k + radius * sin(theta));

	//		glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
	//		glVertex3f(h + radius * cos(theta + interval), start, k + radius * sin(theta + interval));
	//		// bottom
	//		/*glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(start + 0.5, start + 0.5);
	//		glVertex3f(h + start, start , k + start);*/

	//		glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
	//		glVertex3f(h + radius * cos(theta), start + h, k + radius * sin(theta));

	//		glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
	//		glVertex3f(h + radius * cos(theta + interval), start + h, k + radius * sin(theta + interval));
	//	} glEnd();
	//	theta += interval;
	//}
	for (int i = 0; i < edges; ++i) {
		glBegin(GL_TRIANGLE_STRIP); {
			// top
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(h + start, start, k + start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta), start, k + radius * sin(theta));

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta + interval), start, k + radius * sin(theta + interval));
			// bottom
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(h + start, start + h , k + start);

			/*glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta), start + h, k + radius * sin(theta));

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(h + radius * cos(theta + interval), start + h, k + radius * sin(theta + interval));*/
		} glEnd();
		theta += interval;
	}
}


//float* Shape::moveCube(float x, float y, float z, float* cube_verts) {
//	//for (int i = 0; i < sizeof(cube_verts) / sizeof(cube_verts[0]); ++i) {
//	for (int i = 0; i < 36; ++i) {
//		if (i % 3 == 0) {
//			if (cube_verts[i] >= 0) { cube_verts[i] = x; }
//			else { cube_verts[i] = -x; }
//		}
//		else if (i % 3 == 1) {
//			if (cube_verts[i] >= y) { cube_verts[i] = y; }
//			else { cube_verts[i] = -y; }
//		}
//		else if (i % 3 == 2) {
//			if (cube_verts[i] >= z) cube_verts[i] = z;
//			else cube_verts[i] = -z;
//		}
//	}
//	return cube_verts;
//}
