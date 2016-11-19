#include "Skybox.h"
#include "Cube.h"
#include "Icosahedron.h"
#include "Shape.h"

extern GLubyte indices[] = {
	0,   1,   2,	//front
	0,   2,   3,
};

extern GLfloat colors[] = {
	1.0, 0.2, 0.2,
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
	for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); ++i) {
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

void Shape::drawFloor(float x, float y, float z) {
	glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES); {
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(x + -1, y + -1, z + -1);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(x + 1, y + -1, z + -1);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(x + 1, y + -1, z + 1);
	} glEnd();
	glBegin(GL_TRIANGLES); {
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(x + 1, y + -1, z + 1);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(x + -1, y + -1, z + 1);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(x + -1, y + -1, z + -1);
	} glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Shape::drawSquare(float x, float y, float z, GLuint *texture) {
	glBindTexture(GL_TEXTURE_2D, *texture); {
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
		glBegin(GL_TRIANGLES); {
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(x + -1, y + -1, z + -1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(x + 1, y + -1, z + -1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(x + 1, y + -1, z + 1);
		} glEnd();
		glBegin(GL_TRIANGLES); {
			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(x + 1, y + -1, z + 1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 0);
			glVertex3f(x + -1, y + -1, z + 1);

			glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(x + -1, y + -1, z + -1);
		} glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	} glBindTexture(GL_TEXTURE_2D, NULL);
}

void Shape::renderCube(GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, cube_verts);
	glNormalPointer(GL_FLOAT, 0, cube_norms);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texcoords);

	int size = (int)(sizeof(cube_verts)) / (int)(sizeof(cube_verts[0])) / 3;

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::drawBlendCube(GLuint * texture) {
	glPolygonMode(GL_FRONT, GL_LINE);
	renderCube(texture);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	renderCube(texture);
	glPolygonMode(GL_BACK, GL_FILL);
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

//void Shape::drawTorus(int numc, int numt) {
//	int i, j, k;
//	double s, t, x, y, z, twopi;
//
//	twopi = 2 * (double)M_PI;
//	for (i = 0; i < numc; i++) {
//		glBegin(GL_QUAD_STRIP);
//		for (j = 0; j <= numt; j++) {
//			for (k = 1; k >= 0; k--) {
//				s = (i + k) % numc + 0.5;
//				t = j % numt;
//
//				x = (1 + .1*cos(s*twopi / numc))*cos(t*twopi / numt);
//				y = (1 + .1*cos(s*twopi / numc))*sin(t*twopi / numt);
//				z = .1 * sin(s * twopi / numc);
//				glVertex3f(x, y, z);
//			}
//		}
//		glEnd();
//	}
//}

void Shape::buildCircle(int edges, float x, float y, float z) {
	for (int i = 0; i < edges; ++i) {
		//glNormal3f(0.0, 1.0, 0.0);
		//glTexCoord2f(x + (cos((2 * M_PI * i) / edges)), y + (sin((2 * M_PI * i) / edges)));
		circle_verts.push_back(x + (cos((2 * M_PI * i) / edges)));
		circle_verts.push_back(y + (sin((2 * M_PI * i) / edges)));
		circle_verts.push_back(z + 0.0);
	}
}

void Shape::renderCircle() {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	
	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, circle_verts.data());
	
	glDrawArrays(GL_TRIANGLES, 0, circle_verts.size() / 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
}

void Shape::drawCircle(int edges, float x, float y, float z) {
	// version I
	//glBegin(GL_LINE_LOOP); {
	glBegin(GL_LINE_SMOOTH); {
		for (int i = 0; i < edges; ++i) {
			glNormal3f(0.0, 1.0, 0.0);
			glTexCoord2f(x + (cos((2 * M_PI * i) / edges)), y + (sin((2 * M_PI * i) / edges)));
			glVertex3f(x + (cos((2 * M_PI * i) / edges)), y + (sin((2 * M_PI * i) / edges)), z + 0.0);
		}
	} glEnd();
	// version II
	/*glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= edges; i++) {
	if (i == edges) glVertex2f(cos(0), sin(0));
	else glVertex2f(cos((2 * M_PI*i) / edges), sin((2 * M_PI*i) / edges));
	}
	glEnd();*/
}

void Shape::drawSphereTorus(int edges, float x, float y, float z, float rot_interval) {
	// version I
	for (float j = 0.0; j < 360.0; j += rot_interval) {
		glPushMatrix(); {
			glRotatef(j, 0.0f, 1.0f, 0.0f);
			glBegin(GL_LINE_LOOP); {
				for (int i = 0; i < edges; ++i) {
					glVertex3f(x + (cos((2 * M_PI * i) / edges)), y + (sin((2 * M_PI * i) / edges)), z + 0.0);
				}
			} glEnd();
		} glPopMatrix();
	}
	// version II
	/*glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= edges; i++) {
	if (i == edges) glVertex2f(cos(0), sin(0));
	else glVertex2f(cos((2 * M_PI*i) / edges), sin((2 * M_PI*i) / edges));
	}
	glEnd();*/
}

void Shape::buildDisc(int edges, float radius, float x, float y, float z) {
	float 
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

	for (int i = 0; i < edges; ++i) {
		disc_verts.push_back(x + start);
		disc_verts.push_back(y + start);
		disc_verts.push_back(z + start);
		disc_verts.push_back(x + radius * cos(theta));
		disc_verts.push_back(y + radius * sin(theta));
		disc_verts.push_back(z + start);
		disc_verts.push_back(x + radius * cos(theta + interval));
		disc_verts.push_back(y + radius * sin(theta + interval));
		disc_verts.push_back(z + start);

		disc_norms.push_back(0.0);
		disc_norms.push_back(0.0);
		disc_norms.push_back(1.0);
		disc_norms.push_back(0.0);
		disc_norms.push_back(0.0);
		disc_norms.push_back(1.0);
		disc_norms.push_back(0.0);
		disc_norms.push_back(0.0);
		disc_norms.push_back(1.0);

		disc_texcoords.push_back(start + 0.5);
		disc_texcoords.push_back(start + 0.5);
		disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta) / diameter + 0.5);
		disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta) / diameter + 0.5);

		theta += interval;
		}
}

void Shape::renderDisc(GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, *texture);
	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, disc_verts.data());
	glNormalPointer(GL_FLOAT, 0, disc_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, disc_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLES, 0, disc_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::drawDisc(int edges, float radius, float x, float y, float z, GLuint * texture) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;
		for (int i = 0; i < edges; ++i) {
	glBindTexture(GL_TEXTURE_2D, *texture); {
			glBegin(GL_TRIANGLE_FAN);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(x + start, y + start, z + start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(x + radius * cos(theta), y + radius * sin(theta), z + start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(x + radius * cos(theta + interval), y + radius * sin(theta + interval), z + start);
			glEnd();
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
}

void Shape::buildFlatDisc(int edges, float radius, float x, float z) {
	float
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

	for (int i = 0; i < edges; ++i) {
		flat_disc_verts.push_back(x + start);
		flat_disc_verts.push_back(start);
		flat_disc_verts.push_back(z + start);
		flat_disc_verts.push_back(x + radius * cos(theta));
		flat_disc_verts.push_back(start);
		flat_disc_verts.push_back(z + radius * sin(theta));
		flat_disc_verts.push_back(x + radius * cos(theta + interval));
		flat_disc_verts.push_back(start);
		flat_disc_verts.push_back(z + radius * sin(theta + interval));

		flat_disc_norms.push_back(0.0);
		flat_disc_norms.push_back(1.0);
		flat_disc_norms.push_back(0.0);
		flat_disc_norms.push_back(0.0);
		flat_disc_norms.push_back(1.0);
		flat_disc_norms.push_back(0.0);
		flat_disc_norms.push_back(0.0);
		flat_disc_norms.push_back(1.0);
		flat_disc_norms.push_back(0.0);

		flat_disc_texcoords.push_back(start + 0.5);
		flat_disc_texcoords.push_back(start + 0.5);
		flat_disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		flat_disc_texcoords.push_back(sin(theta) / diameter + 0.5);
		flat_disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		flat_disc_texcoords.push_back(sin(theta) / diameter + 0.5);

		theta += interval;
	}
}

void Shape::renderFlatDisc(GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, *texture);
	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, flat_disc_verts.data());
	glNormalPointer(GL_FLOAT, 0, flat_disc_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, flat_disc_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLES, 0, flat_disc_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::drawFlatDisc(int edges, float radius, float x, float z, GLuint * texture) {
	float
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

		for (int i = 0; i < edges; ++i) {
			glBindTexture(GL_TEXTURE_2D, *texture); {
			glBegin(GL_TRIANGLE_FAN);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(start + 0.5, start + 0.5);
			glVertex3f(x + start, start, z + start);

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(x + radius * cos(theta), start, z + radius * sin(theta));

			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
			glVertex3f(x + radius * cos(theta + interval), start, z + radius * sin(theta + interval));
			glEnd();
			theta += interval;
			} glBindTexture(GL_TEXTURE_2D, NULL);
		}
}

//void Shape::normalize(float v[3]) {
//	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
//	if (d == 0.0) {
//		return;
//	}
//	v[0] /= d; v[1] /= d; v[2] /= d;
//}
//
//void Shape::normcrossprod(float v1[3], float v2[3], float out[3]) {
//	GLint i, j;
//	GLfloat length;
//
//	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
//	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
//	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
//	normalize(out);
//}

//void Shape::drawIcosahedron() {
//	//glBegin(GL_TRIANGLES);
//	//for (int i = 0; i < 20; i++) {
//	//	glNormal3fv(&vdata[tindices[i][0]][0]);
//	//	glVertex3fv(&vdata[tindices[i][0]][0]);
//	//	glNormal3fv(&vdata[tindices[i][1]][0]);
//	//	glVertex3fv(&vdata[tindices[i][1]][0]);
//	//	glNormal3fv(&vdata[tindices[i][2]][0]);
//	//	glVertex3fv(&vdata[tindices[i][2]][0]);
//	//}
//	//glEnd();
//
//
//	for (int i = 0; i < 20; i++) {
//		subdivide(&vdata[tindices[i][0]][0],
//			&vdata[tindices[i][1]][0],
//			&vdata[tindices[i][2]][0]);
//	}
//	/*glBegin(GL_TRIANGLES);
//	for (int i = 0; i < 50; i++) {
//		float d1[3], d2[3], norm[3];
//		for (int j = 0; j < 3; j++) {
//			d1[j] = vdata[tindices[i][0]][j] - vdata[tindices[i][1]][j];
//			d2[j] = vdata[tindices[i][1]][j] - vdata[tindices[i][2]][j];
//		}
//
//		normcrossprod(d1, d2, norm);
//		glNormal3fv(norm);
//		glVertex3fv(&vdata[tindices[i][0]][0]);
//		glVertex3fv(&vdata[tindices[i][1]][0]);
//		glVertex3fv(&vdata[tindices[i][2]][0]);
//	}
//	glEnd();*/
//}
//no need to use inline since a function defined entirely inside a class/struct/union definition, 
//whether it's a member function or a non-member friend function, 
//is implicitly an inline function.

float Shape::calc_x0(float radius, float theta, float delta) {
	return radius * cos(theta) * sin(delta);
}
float Shape::calc_y0(float radius, float theta, float delta) {
	return radius * cos(delta);
}
float Shape::calc_z0(float radius, float theta, float delta) {
	return radius * sin(theta) * sin(delta);
}

float Shape::calc_x1(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(theta) * sin(delta + delta_interval);
}
float Shape::calc_y1(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(delta + delta_interval);
}
float Shape::calc_z1(float radius, float theta, float delta, float delta_interval) {
	return radius * sin(theta) * sin(delta + delta_interval);
}

float Shape::calc_x2(float radius, float theta, float theta_interval, float delta, float delta_interval) {
	return radius * cos(theta + theta_interval) * sin(delta + delta_interval);
}
float Shape::calc_y2(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(delta + delta_interval);
}
float Shape::calc_z2(float radius, float theta, float theta_interval, float delta, float delta_interval) {
	return radius * sin(theta + theta_interval) * sin(delta + delta_interval);
}

float Shape::calc_x3(float radius, float theta, float theta_interval, float delta) {
	return radius * cos(theta + theta_interval) * sin(delta);
}
float Shape::calc_y3(float radius, float theta, float theta_interval, float delta) {
	return radius * cos(delta);
}
float Shape::calc_z3(float radius, float theta, float theta_interval, float delta) {
	return radius * sin(theta + theta_interval) * sin(delta);
}

float Shape::calc_n_x0(float radius, float theta, float delta) {
	return cos(theta) * sin(delta) / radius;
}
float Shape::calc_n_y0(float radius, float theta, float delta) {
	return cos(delta) / radius;
}
float Shape::calc_n_z0(float radius, float theta, float delta) {
	return sin(theta) * sin(delta) / radius;
}

float Shape::calc_n_x1(float radius, float theta, float delta, float delta_interval) {
	return cos(theta) * sin(delta + delta_interval) / radius;
}
float Shape::calc_n_y1(float radius, float theta, float delta, float delta_interval) {
	return cos(delta + delta_interval) / radius;
}
float Shape::calc_n_z1(float radius, float theta, float delta, float delta_interval) {
	return sin(theta) * sin(delta + delta_interval) / radius;
}

float Shape::calc_n_x2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return cos(theta + theta_interval) * sin(delta + delta_interval) / radius;
}
float Shape::calc_n_y2(float radius, float theta, float delta, float delta_interval) {
	return cos(delta + delta_interval) / radius;
}
float Shape::calc_n_z2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return sin(theta + theta_interval) * sin(delta + delta_interval) / radius;
}

float Shape::calc_n_x3(float radius, float theta, float delta, float theta_interval) {
	return cos(theta + theta_interval) * sin(delta) / radius;
}
float Shape::calc_n_y3(float radius, float theta, float delta, float theta_interval) {
	return cos(delta) / radius;
}
float Shape::calc_n_z3(float radius, float theta, float delta, float theta_interval) {
	return sin(theta + theta_interval) * sin(delta) / radius;
}

void Shape::buildSphere(double radius, double latitude, double longitude) {
	double
		delta = 0.0, // angle of latitude
		theta = 0.0, // angle of longitude
		theta_interval = (2.0 * M_PI) / latitude, // angle of latitude
		delta_interval = M_PI / longitude, // angle of longitude
		u_lats = 0.0,
		v_longs = 0.0,
		u_lats_interval = 1.0 / latitude,
		v_longs_interval = 1.0 / longitude;

	for (int i = 0; i < longitude; ++i) {
		for (int j = 0; j < latitude; ++j) {
			sphere_verts.push_back(calc_x0(radius, theta, delta));
			sphere_verts.push_back(calc_y0(radius, theta, delta));
			sphere_verts.push_back(calc_z0(radius, theta, delta));

			sphere_verts.push_back(calc_x1(radius, theta, delta, delta_interval));
			sphere_verts.push_back(calc_y1(radius, theta, delta, delta_interval));
			sphere_verts.push_back(calc_z1(radius, theta, delta, delta_interval));

			sphere_verts.push_back(calc_x2(radius, theta, theta_interval, delta, delta_interval));
			sphere_verts.push_back(calc_y2(radius, theta, delta, delta_interval));
			sphere_verts.push_back(calc_z2(radius, theta, theta_interval, delta, delta_interval));

			sphere_verts.push_back(calc_x2(radius, theta, theta_interval, delta, delta_interval));
			sphere_verts.push_back(calc_y2(radius, theta, delta, delta_interval));
			sphere_verts.push_back(calc_z2(radius, theta, theta_interval, delta, delta_interval));

			sphere_verts.push_back(calc_x3(radius, theta, theta_interval, delta));
			sphere_verts.push_back(calc_y3(radius, theta, theta_interval, delta));
			sphere_verts.push_back(calc_z3(radius, theta, theta_interval, delta));

			sphere_verts.push_back(calc_x0(radius, theta, delta));
			sphere_verts.push_back(calc_y0(radius, theta, delta));
			sphere_verts.push_back(calc_z0(radius, theta, delta));


			sphere_norms.push_back(calc_n_x0(radius, theta, delta));
			sphere_norms.push_back(calc_n_y0(radius, theta, delta));
			sphere_norms.push_back(calc_n_z0(radius, theta, delta));

			sphere_norms.push_back(calc_n_x1(radius, theta, delta, delta_interval));
			sphere_norms.push_back(calc_n_y1(radius, theta, delta, delta_interval));
			sphere_norms.push_back(calc_n_z1(radius, theta, delta, delta_interval));

			sphere_norms.push_back(calc_n_x2(radius, theta, delta, delta_interval, theta_interval));
			sphere_norms.push_back(calc_n_y2(radius, theta, delta, delta_interval));
			sphere_norms.push_back(calc_n_z2(radius, theta, delta, delta_interval, theta_interval));

			sphere_norms.push_back(calc_n_x2(radius, theta, delta, delta_interval, theta_interval));
			sphere_norms.push_back(calc_n_y2(radius, theta, delta, delta_interval));
			sphere_norms.push_back(calc_n_z2(radius, theta, delta, delta_interval, theta_interval));

			sphere_norms.push_back(calc_n_x3(radius, theta, delta, theta_interval));
			sphere_norms.push_back(calc_n_y3(radius, theta, delta, theta_interval));
			sphere_norms.push_back(calc_n_z3(radius, theta, delta, theta_interval));

			sphere_norms.push_back(calc_n_x0(radius, theta, delta));
			sphere_norms.push_back(calc_n_y0(radius, theta, delta));
			sphere_norms.push_back(calc_n_z0(radius, theta, delta));


			sphere_texcoords.push_back(v_longs);
			sphere_texcoords.push_back(u_lats);

			sphere_texcoords.push_back(v_longs);
			sphere_texcoords.push_back(u_lats + u_lats_interval);

			sphere_texcoords.push_back(v_longs + v_longs_interval);
			sphere_texcoords.push_back(u_lats + u_lats_interval);

			sphere_texcoords.push_back(v_longs + v_longs_interval);
			sphere_texcoords.push_back(u_lats + u_lats_interval);

			sphere_texcoords.push_back(v_longs + v_longs_interval);
			sphere_texcoords.push_back(u_lats);

			sphere_texcoords.push_back(v_longs);
			sphere_texcoords.push_back(u_lats);


			theta += theta_interval;
			v_longs += v_longs_interval;
		}
		u_lats += u_lats_interval;
		theta = 0.0; v_longs = 0.0;
		delta += delta_interval;
	}
}

void Shape::renderSphere(GLuint *texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindTexture(GL_TEXTURE_2D, *texture);
	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, sphere_verts.data());
	glNormalPointer(GL_FLOAT, 0, sphere_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, sphere_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLES, 0, sphere_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::drawSphere(double radius, double latitude, double longitude, GLuint * texture) {
	double
		delta = 0.0, // angle of latitude
		theta = 0.0, // angle of longitude
		theta_interval = (2.0 * M_PI) / latitude, // angle of latitude
		delta_interval = M_PI / longitude, // angle of longitude
		u_lats = 0.0,
		v_longs = 0.0,
		u_lats_interval = 1.0 / latitude,
		v_longs_interval = 1.0 / longitude;
	
	for (int i = 0; i < longitude; ++i) {
		for (int j = 0; j < latitude; ++j) {
			double
				x0 = calc_x0(radius, theta, delta),
				y0 = calc_y0(radius, theta, delta),
				z0 = calc_z0(radius, theta, delta),
				n_x0 = calc_n_x0(radius, theta, delta),
				n_y0 = calc_n_y0(radius, theta, delta),
				n_z0 = calc_n_z0(radius, theta, delta),
				v0 = u_lats,
				u0 = v_longs + v_longs_interval,

				x1 = calc_x1(radius, theta, delta, delta_interval),
				y1 = calc_y1(radius, theta, delta, delta_interval),
				z1 = calc_z1(radius, theta, delta, delta_interval),
				n_x1 = calc_n_x1(radius, theta, delta, delta_interval),
				n_y1 = calc_n_y1(radius, theta, delta, delta_interval),
				n_z1 = calc_n_z1(radius, theta, delta, delta_interval),
				v1 = u_lats + u_lats_interval,
				u1 = v_longs + v_longs_interval,

				x2 = calc_x2(radius, theta, theta_interval, delta, delta_interval),
				y2 = calc_y2(radius, theta, delta, delta_interval),
				z2 = calc_z2(radius, theta, theta_interval, delta, delta_interval),
				n_x2 = calc_n_x2(radius, theta, delta, delta_interval, theta_interval),
				n_y2 = calc_n_y2(radius, theta, delta, delta_interval),
				n_z2 = calc_n_z2(radius, theta, delta, delta_interval, theta_interval),
				v2 = u_lats + u_lats_interval,
				u2 = v_longs,

				x3 = calc_x3(radius, theta, theta_interval, delta),
				y3 = calc_y3(radius, theta, theta_interval, delta),
				z3 = calc_z3(radius, theta, theta_interval, delta),
				n_x3 = calc_n_x3(radius, theta, delta, theta_interval),
				n_y3 = calc_n_y3(radius, theta, delta, theta_interval),
				n_z3 = calc_n_z3(radius, theta, delta, theta_interval),
				v3 = u_lats,
				u3 = v_longs;

			glBindTexture(GL_TEXTURE_2D, *texture); {
			glBegin(GL_TRIANGLE_STRIP); {
				glTexCoord2f(u0, v0); // 0
				glNormal3f(n_x0, n_y0, n_z0);
				glVertex3f(x0, y0, z0);
				/*glTexCoord2f(0.5 + (atan2(radius * cos(theta) * sin(delta),
									radius * sin(theta) * sin(delta)) / 2 * M_PI),
							(0.5 - (asin(radius * cos(delta)) / M_PI)));*/

				glTexCoord2f(u1, v1); // 1
				glNormal3f(n_x1, n_y1, n_z1);
				glVertex3f(x1, y1, z1);
				/*glTexCoord2f(0.5 + (atan2(radius * cos(theta) * sin(delta_interval),
					radius * sin(theta) * sin(delta_interval)) / 2 * M_PI),
					(0.5 - (asin(radius * cos(delta_interval)) / M_PI)));*/

				glTexCoord2f(u2, v2); // 2
				glNormal3f(n_x2, n_y2, n_z2);
				glVertex3f(x2, y2, z2);
				/*glTexCoord2f(0.5 + (atan2(radius * cos(theta_interval) * sin(delta_interval),
					radius * sin(theta_interval) * sin(delta_interval)) / 2 * M_PI),
					(0.5 - (asin(radius * cos(delta_interval)) / M_PI)));*/

				glTexCoord2f(u2, v2); // 2
				glNormal3f(n_x2, n_y2, n_z2);
				glVertex3f(x2, y2, z2);
				/*glTexCoord2f(0.5 + (atan2(radius * cos(theta_interval) * sin(delta_interval),
					radius * sin(theta_interval) * sin(delta_interval)) / 2 * M_PI),
					(0.5 - (asin(radius * cos(delta_interval)) / M_PI)));*/

				glTexCoord2f(u3, v3); // 3
				glNormal3f(n_x0, n_y0, n_z0);
				glVertex3f(x3, y3, z3);
				/*glTexCoord2f(0.5 + (atan2(radius * cos(theta_interval) * sin(delta),
					radius * sin(theta_interval) * sin(delta)) / 2 * M_PI),
					(0.5 - (asin(radius * cos(delta)) / M_PI)));*/

				glTexCoord2f(u0, v0); // 0
				glNormal3f(n_x0, n_y0, n_z0);
				glVertex3f(x0, y0, z0);
				/*glTexCoord2f(0.5 + (atan2(radius * cos(theta) * sin(delta),
					radius * sin(theta) * sin(delta)) / 2 * M_PI),
					(0.5 - (asin(radius * cos(delta)) / M_PI)));*/
			} glEnd();
			} glBindTexture(GL_TEXTURE_2D, NULL);
			theta += theta_interval;
			v_longs += v_longs_interval;
		}
		u_lats += u_lats_interval;
		theta = 0.0; v_longs = 0.0;
		delta += delta_interval;
	}

	/*for (int i = 0; i <= lats; i++) {
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
	}*/
}

void Shape::drawCylinder(float radius, float edges, float height, float x, float y, float z, GLuint * texture) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;

	glBindTexture(GL_TEXTURE_2D, *texture); {
		for (int i = 0; i < edges; ++i) {
			glBegin(GL_TRIANGLE_STRIP); {
				// bottom
				// Middle of bottom disc
				glNormal3f((x + start) / radius, (y + start) / radius, (z + start) / radius);
				//glTexCoord2f(	start + 0.5,									start + 0.5																				);
				glTexCoord2f(start + 0.25, start + 0.25);
				glVertex3f(x + start, y + start, z + start);

				// Triangle's first edge
				glNormal3f((x + radius * cos(theta) / radius), (y + start) / radius, (z + radius * sin(theta)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.25, sin(theta) / diameter + 0.25);
				glVertex3f(x + radius * cos(theta), y + start, z + radius * sin(theta));
				// Triangle's second edge

				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start) / radius, (z + radius * sin(theta + interval)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.25, sin(theta) / diameter + 0.25);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
				// top. Adding height to Y coordinates
				// Middle of top disc

				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));
				// Triangle's second edge

				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start + height) / radius, (z + radius * sin(theta + interval)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta + interval), y + start + height, z + radius * sin(theta + interval));
				// Triangle's second edge

				glNormal3f((x + start) / radius, (y + start + height) / radius, (z + start) / radius);
				//glTexCoord2f(	start + 0.5,									start + 0.5																				);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start + height, z + start);

			} glEnd();
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
}

void Shape::drawCylinderLowPoli(float radius, float edges, float height, float x, float y, float z, GLuint *disk_texture, GLuint *side_texture) {
	float
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

	glBindTexture(GL_TEXTURE_2D, *disk_texture); {
		for (int i = 0; i < edges; ++i) {
			glBegin(GL_TRIANGLE_FAN); {
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start, z + start);

				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta), y + start, z + radius * sin(theta));

				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
			} glEnd();
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
	// side
	theta = 0.0;
	glBindTexture(GL_TEXTURE_2D, *side_texture); {
		for (int j = 0; j < edges; ++j) {
			glBegin(GL_TRIANGLE_STRIP); {
				// 0 bottom 
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(0, 1);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
				// 1 bottom
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(1, 1);
				glVertex3f(x + radius * cos(theta), y + start, z + radius * sin(theta));
				// 2 top
				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				glTexCoord2f(1, 0);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));
				// 2 top
				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				glTexCoord2f(1, 0);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));
				// 3 top
				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start + height) / radius, (z + radius * sin(theta + interval)) / radius);
				glTexCoord2f(0, 0);
				glVertex3f(x + radius * cos(theta + interval), y + start + height, z + radius * sin(theta + interval));
				// 0 bottom 
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(0, 1);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
			} glEnd();
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
	// bottom disk
	theta = 0.0;
	glBindTexture(GL_TEXTURE_2D, *disk_texture); {
		for (int i = 0; i < edges; ++i) {
			glBegin(GL_TRIANGLE_FAN); {
				// Middle
				glNormal3f((x + start) / radius, (y + start + height) / radius, (z + start) / radius);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start + height, z + start);

				// Tringle's first edge
				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));

				// Triangle's second edge
				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start + height) / radius, (z + radius * sin(theta + interval)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta + interval), y + start + height, z + radius * sin(theta + interval));
			} glEnd();
			theta += interval;
		} glBindTexture(GL_TEXTURE_2D, NULL);
	}
}

void Shape::drawCylinderHighPoli(float radius, float edges, float height, float x, float y, float z, GLuint *disk_texture, GLuint *side_texture) {
	float
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0,
		v = 0.0,
		u = 0.0,
		u_inter = 1.0 / edges;

	glBindTexture(GL_TEXTURE_2D, *disk_texture); {
		for (int i = 0; i < edges; ++i) {
			glBegin(GL_TRIANGLE_FAN); {
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start, z + start);

				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta), y + start, z + radius * sin(theta));

				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
			} glEnd();
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
	// side
	theta = 0.0;
	glBindTexture(GL_TEXTURE_2D, *side_texture); {
		for (int j = 0; j < edges; ++j) {
			glBegin(GL_TRIANGLE_STRIP); {
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(u, 1);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
				// 1 bottom
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(u + u_inter, 1);
				glVertex3f(x + radius * cos(theta), y + start, z + radius * sin(theta));
				// 2 top
				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				glTexCoord2f(u + u_inter, 0);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));
				// 2 top
				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				glTexCoord2f(u + u_inter, 0);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));
				// 3 top
				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start + height) / radius, (z + radius * sin(theta + interval)) / radius);
				glTexCoord2f(u, 0);
				glVertex3f(x + radius * cos(theta + interval), y + start + height, z + radius * sin(theta + interval));
				// 0 bottom 
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(u, 1);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
			} glEnd();
			u += u_inter;
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
	// bottom disk
	theta = 0.0;
	glBindTexture(GL_TEXTURE_2D, *disk_texture); {
		for (int i = 0; i < edges; ++i) {
			glBegin(GL_TRIANGLE_FAN); {
				// Middle
				glNormal3f((x + start) / radius, (y + start + height) / radius, (z + start) / radius);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start + height, z + start);

				// Tringle's first edge
				glNormal3f((x + radius * cos(theta)) / radius, (y + start + height) / radius, (z + radius * sin(theta)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta), y + start + height, z + radius * sin(theta));

				// Triangle's second edge
				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start + height) / radius, (z + radius * sin(theta + interval)) / radius);
				//glTexCoord2f(	cos(theta) / diameter + 0.5,					sin(theta) / diameter + 0.5																);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta + interval), y + start + height, z + radius * sin(theta + interval));
			} glEnd();
			theta += interval;
		} glBindTexture(GL_TEXTURE_2D, NULL);
	}
}

void Shape::drawCone(float radius, float edges, float height, float x, float y, float z, GLuint * texture) {
	float interval = 2.0 * M_PI / edges;
	float diameter = 2 * radius;
	float start = 0.0;
	float theta = 0.0;

	glBindTexture(GL_TEXTURE_2D, *texture); {
		for (int i = 0; i < edges; ++i) {
			glBegin(GL_TRIANGLE_STRIP); {
				// bottom disk
				glNormal3f((x + start) / radius, (y + start) / radius, (z + start) / radius);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start, z + start);
				// 
				glNormal3f((x + radius * cos(theta) / radius), (y + start) / radius, (z + radius * sin(theta)) / radius);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta), y + start, z + radius * sin(theta));
				//
				glNormal3f((x + radius * cos(theta + interval)) / radius, (y + start) / radius, (z + radius * sin(theta + interval)) / radius);
				glTexCoord2f(cos(theta) / diameter + 0.5, sin(theta) / diameter + 0.5);
				glVertex3f(x + radius * cos(theta + interval), y + start, z + radius * sin(theta + interval));
				// tip
				glNormal3f((x + start) / radius, (y + start + height) / radius, (z + start) / radius);
				//glTexCoord2f(	1 / edges,											1 / edges																			);
				glTexCoord2f(start + 0.5, start + 0.5);
				glVertex3f(x + start, y + start + height, z + start);
			} glEnd();
			theta += interval;
		}
	} glBindTexture(GL_TEXTURE_2D, NULL);
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
