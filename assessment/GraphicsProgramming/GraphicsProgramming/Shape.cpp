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

	glBegin(GL_TRIANGLE_STRIP);
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

	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::buildFloor(float x, float y, float z) {
	floor_verts = { (x + -1),
					(y + -1),
					(z + -1),
					(x + 1),
					(y + -1),
					(z + -1),
					(x + 1),
					(y + -1),
					(z + 1),
					(x + 1),
					(y + -1),
					(z + 1),
					(x + -1),
					(y + -1),
					(z + 1),
					(x + -1),
					(y + -1),
					(z + -1) };

	for (int i = 0; i < 6; ++i) {
		floor_norms.push_back(0.0f);
		floor_norms.push_back(1.0f);
		floor_norms.push_back(0.0f);
	}

	floor_texcoords = { 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1 };

	floor_colors = { 0.5, 0.5, 0.5, 0.5 };
}

void Shape::renderFloor(float R, float G, float B, float A) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, floor_colors.data());
	glVertexPointer(3, GL_FLOAT, 0, floor_verts.data());
	glNormalPointer(GL_FLOAT, 0, floor_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, floor_texcoords.data());

	glColor4f(R, G, B, A);
	glDrawArrays(GL_TRIANGLES, 0, floor_verts.size() / 3);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

void Shape::renderBlendCube(GLuint * texture) {
	glPolygonMode(GL_FRONT, GL_LINE);
	renderCube(texture);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	renderCube(texture);
	glPolygonMode(GL_BACK, GL_FILL);
}

void Shape::renderSkybox(GLuint *texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, skybox_verts);
	glNormalPointer(GL_FLOAT, 0, skybox_norms);
	glTexCoordPointer(2, GL_FLOAT, 0, skybox_texcoords);

	glBindTexture(GL_TEXTURE_2D, *texture); {
	glDrawArrays(GL_TRIANGLES, 0, 36);
	} glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

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
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, circle_verts.size() / 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
}

float Shape::disc_sin(float pos, float radius, float theta) {
	return pos + radius * cos(theta);
}
float Shape::disc_cos(float pos, float radius, float theta) {
	return pos + radius * sin(theta);
}
float Shape::disc_sin_n(float pos, float radius, float theta)
{
	return (pos + radius * sin(theta)) / radius;
}
float Shape::disc_cos_n(float pos, float radius, float theta)
{
	return (pos + radius * cos(theta)) / radius; // TODO should pos be in the brackets?
}

void Shape::buildDisc(int edges, float radius, float x, float y, float z) {
	float 
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

	for (int i = 0; i < edges; ++i) {
		disc_verts.push_back(x);
		disc_verts.push_back(y);
		disc_verts.push_back(z);
		disc_verts.push_back(disc_cos(x, radius, theta));
		disc_verts.push_back(disc_sin(y, radius, theta));
		disc_verts.push_back(z);
		disc_verts.push_back(disc_cos(x, radius, theta + interval));
		disc_verts.push_back(disc_sin(y, radius, theta + interval));
		disc_verts.push_back(z);

		for (int i = 0; i < 3; ++i) {
			disc_norms.push_back(0.0);
			disc_norms.push_back(0.0);
			disc_norms.push_back(1.0);
		}

		disc_texcoords.push_back(0.5);
		disc_texcoords.push_back(0.5);
		disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta) / diameter + 0.5);
		disc_texcoords.push_back(cos(theta + interval) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta + interval) / diameter + 0.5);

		theta += interval;
		}
}

void Shape::renderDisc(GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, disc_verts.data());
	glNormalPointer(GL_FLOAT, 0, disc_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, disc_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, disc_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::buildFlatDisc(int edges, float radius, float x, float z) {
	float
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

	for (int i = 0; i < edges; ++i) {
		disc_verts.push_back(x);
		disc_verts.push_back(start);
		disc_verts.push_back(z);
		disc_verts.push_back(x + radius * cos(theta));
		disc_verts.push_back(start);
		disc_verts.push_back(z + radius * sin(theta));
		disc_verts.push_back(x + radius * cos(theta + interval));
		disc_verts.push_back(start);
		disc_verts.push_back(z + radius * sin(theta + interval));

		for (int i = 0; i < 3; ++i) {
			disc_norms.push_back(0.0);
			disc_norms.push_back(1.0);
			disc_norms.push_back(0.0);
		}

		disc_texcoords.push_back(0.5);
		disc_texcoords.push_back(0.5);
		disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta) / diameter + 0.5);
		disc_texcoords.push_back(cos(theta + interval) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta + interval) / diameter + 0.5);

		theta += interval;
	}
}

void Shape::renderFlatDisc(GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, disc_verts.data());
	glNormalPointer(GL_FLOAT, 0, disc_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, disc_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, disc_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//no need to use inline since a function defined entirely inside a class/struct/union definition, 
//whether it's a member function or a non-member friend function, 
//is implicitly an inline function.
float Shape::sphere_x0(float radius, float theta, float delta) {
	return radius * cos(theta) * sin(delta);
}
float Shape::sphere_y0(float radius, float theta, float delta) {
	return radius * cos(delta);
}
float Shape::sphere_z0(float radius, float theta, float delta) {
	return radius * sin(theta) * sin(delta);
}

float Shape::sphere_x1(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(theta) * sin(delta + delta_interval);
}
float Shape::sphere_y1(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(delta + delta_interval);
}
float Shape::sphere_z1(float radius, float theta, float delta, float delta_interval) {
	return radius * sin(theta) * sin(delta + delta_interval);
}

float Shape::sphere_x2(float radius, float theta, float theta_interval, float delta, float delta_interval) {
	return radius * cos(theta + theta_interval) * sin(delta + delta_interval);
}
float Shape::sphere_y2(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(delta + delta_interval);
}
float Shape::sphere_z2(float radius, float theta, float theta_interval, float delta, float delta_interval) {
	return radius * sin(theta + theta_interval) * sin(delta + delta_interval);
}

float Shape::sphere_x3(float radius, float theta, float theta_interval, float delta) {
	return radius * cos(theta + theta_interval) * sin(delta);
}
float Shape::sphere_y3(float radius, float theta, float theta_interval, float delta) {
	return radius * cos(delta);
}
float Shape::sphere_z3(float radius, float theta, float theta_interval, float delta) {
	return radius * sin(theta + theta_interval) * sin(delta);
}

float Shape::sphere_n_x0(float radius, float theta, float delta) {
	return cos(theta) * sin(delta) / radius;
}
float Shape::sphere_n_y0(float radius, float theta, float delta) {
	return cos(delta) / radius;
}
float Shape::sphere_n_z0(float radius, float theta, float delta) {
	return sin(theta) * sin(delta) / radius;
}

float Shape::sphere_n_x1(float radius, float theta, float delta, float delta_interval) {
	return cos(theta) * sin(delta + delta_interval) / radius;
}
float Shape::sphere_n_y1(float radius, float theta, float delta, float delta_interval) {
	return cos(delta + delta_interval) / radius;
}
float Shape::sphere_n_z1(float radius, float theta, float delta, float delta_interval) {
	return sin(theta) * sin(delta + delta_interval) / radius;
}

float Shape::sphere_n_x2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return cos(theta + theta_interval) * sin(delta + delta_interval) / radius;
}
float Shape::sphere_n_y2(float radius, float theta, float delta, float delta_interval) {
	return cos(delta + delta_interval) / radius;
}
float Shape::sphere_n_z2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return sin(theta + theta_interval) * sin(delta + delta_interval) / radius;
}

float Shape::sphere_n_x3(float radius, float theta, float delta, float theta_interval) {
	return cos(theta + theta_interval) * sin(delta) / radius;
}
float Shape::sphere_n_y3(float radius, float theta, float delta, float theta_interval) {
	return cos(delta) / radius;
}
float Shape::sphere_n_z3(float radius, float theta, float delta, float theta_interval) {
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
			sphere_verts.push_back(sphere_x0(radius, theta, delta));
			sphere_verts.push_back(sphere_y0(radius, theta, delta));
			sphere_verts.push_back(sphere_z0(radius, theta, delta));

			sphere_verts.push_back(sphere_x1(radius, theta, delta, delta_interval));
			sphere_verts.push_back(sphere_y1(radius, theta, delta, delta_interval));
			sphere_verts.push_back(sphere_z1(radius, theta, delta, delta_interval));

			sphere_verts.push_back(sphere_x2(radius, theta, theta_interval, delta, delta_interval));
			sphere_verts.push_back(sphere_y2(radius, theta, delta, delta_interval));
			sphere_verts.push_back(sphere_z2(radius, theta, theta_interval, delta, delta_interval));

			sphere_verts.push_back(sphere_x2(radius, theta, theta_interval, delta, delta_interval));
			sphere_verts.push_back(sphere_y2(radius, theta, delta, delta_interval));
			sphere_verts.push_back(sphere_z2(radius, theta, theta_interval, delta, delta_interval));

			sphere_verts.push_back(sphere_x3(radius, theta, theta_interval, delta));
			sphere_verts.push_back(sphere_y3(radius, theta, theta_interval, delta));
			sphere_verts.push_back(sphere_z3(radius, theta, theta_interval, delta));

			sphere_verts.push_back(sphere_x0(radius, theta, delta));
			sphere_verts.push_back(sphere_y0(radius, theta, delta));
			sphere_verts.push_back(sphere_z0(radius, theta, delta));


			sphere_norms.push_back(sphere_n_x0(radius, theta, delta));
			sphere_norms.push_back(sphere_n_y0(radius, theta, delta));
			sphere_norms.push_back(sphere_n_z0(radius, theta, delta));

			sphere_norms.push_back(sphere_n_x1(radius, theta, delta, delta_interval));
			sphere_norms.push_back(sphere_n_y1(radius, theta, delta, delta_interval));
			sphere_norms.push_back(sphere_n_z1(radius, theta, delta, delta_interval));

			sphere_norms.push_back(sphere_n_x2(radius, theta, delta, delta_interval, theta_interval));
			sphere_norms.push_back(sphere_n_y2(radius, theta, delta, delta_interval));
			sphere_norms.push_back(sphere_n_z2(radius, theta, delta, delta_interval, theta_interval));

			sphere_norms.push_back(sphere_n_x2(radius, theta, delta, delta_interval, theta_interval));
			sphere_norms.push_back(sphere_n_y2(radius, theta, delta, delta_interval));
			sphere_norms.push_back(sphere_n_z2(radius, theta, delta, delta_interval, theta_interval));

			sphere_norms.push_back(sphere_n_x3(radius, theta, delta, theta_interval));
			sphere_norms.push_back(sphere_n_y3(radius, theta, delta, theta_interval));
			sphere_norms.push_back(sphere_n_z3(radius, theta, delta, theta_interval));

			sphere_norms.push_back(sphere_n_x0(radius, theta, delta));
			sphere_norms.push_back(sphere_n_y0(radius, theta, delta));
			sphere_norms.push_back(sphere_n_z0(radius, theta, delta));


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
	
	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, sphere_verts.data());
	glNormalPointer(GL_FLOAT, 0, sphere_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, sphere_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLES, 0, sphere_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::buildCylinder(float radius, float edges, float height, float x, float y, float z) {
	edgesCylinder = (int)(edges);
	float
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		theta = 0.0,
		y_value = height / edges,
		u = 0.0,
		v = 0.0,
		u_inter = 1.0 / edges,
		v_inter = 1.0 / height;

	// bottom disk
	for (int i = 0; i < edges; ++i) {
		disc_verts.push_back(x);
		disc_verts.push_back(y);
		disc_verts.push_back(z);
		disc_verts.push_back(x + radius * cos(theta));
		disc_verts.push_back(y);
		disc_verts.push_back(z + radius * sin(theta));
		disc_verts.push_back(x + radius * cos(theta + interval));
		disc_verts.push_back(y);
		disc_verts.push_back(z + radius * sin(theta + interval));

		for (int i = 0; i < 3; ++i) {
			disc_norms.push_back(0.0);
			disc_norms.push_back(-1.0);
			disc_norms.push_back(0.0);
		}

		disc_texcoords.push_back(0.5);
		disc_texcoords.push_back(0.5);
		disc_texcoords.push_back(cos(theta) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta) / diameter + 0.5);
		disc_texcoords.push_back(cos(theta + interval) / diameter + 0.5);
		disc_texcoords.push_back(sin(theta + interval) / diameter + 0.5);

		theta += interval;
	}
	// top disk
	theta = 0.0;
	for (int i = 0; i < edges; ++i) {
		disc1_verts.push_back(x);
		disc1_verts.push_back(y + y_value * height);
		disc1_verts.push_back(z);
		disc1_verts.push_back(x + radius * cos(theta));
		disc1_verts.push_back(y + y_value * height);
		disc1_verts.push_back(z + radius * sin(theta));
		disc1_verts.push_back(x + radius * cos(theta + interval));
		disc1_verts.push_back(y + y_value * height);
		disc1_verts.push_back(z + radius * sin(theta + interval));

		for (int i = 0; i < 3; ++i) {
			disc1_norms.push_back(0.0);
			disc1_norms.push_back(1.0);
			disc1_norms.push_back(0.0);
		}

		disc1_texcoords.push_back(0.5);
		disc1_texcoords.push_back(0.5);
		disc1_texcoords.push_back(cos(theta) / diameter + 0.5);
		disc1_texcoords.push_back(sin(theta) / diameter + 0.5);
		disc1_texcoords.push_back(cos(theta + interval) / diameter + 0.5);
		disc1_texcoords.push_back(sin(theta + interval) / diameter + 0.5);

		theta += interval;
	}
	// side
	theta = 0.0; 
	for (int i = 1; i <= height; ++i) {
		for (int j = 0; j < edges; ++j) {
			float  y0 = y + y_value * (i - 1);
			float y1 = y + y_value * i;

			// 0 bottom
			verts.push_back(disc_cos(x, radius, theta));
			verts.push_back(y0);
			verts.push_back(disc_sin(z, radius, theta));
			// 1 bottom
			verts.push_back(disc_cos(x, radius, theta + interval));
			verts.push_back(y0);
			verts.push_back(disc_sin(z, radius, theta + interval));
			// 2 top
			verts.push_back(disc_cos(x, radius, theta + interval));
			verts.push_back(y1);
			verts.push_back(disc_sin(z, radius, theta + interval));
			//// 2 top
			//verts.push_back(disc_cos(x, radius, theta + interval));
			//verts.push_back(y1);
			//verts.push_back(disc_sin(z, radius, theta + interval));
			// 3 top
			verts.push_back(disc_cos(x, radius, theta));
			verts.push_back(y1);
			verts.push_back(disc_sin(z, radius, theta));
			// 0 bottom
			verts.push_back(disc_cos(x, radius, theta));
			verts.push_back(y0);
			verts.push_back(disc_sin(z, radius, theta));

			// 0 bottom
			texcoords.push_back(u);
			texcoords.push_back(v);
			// 1 bottom
			texcoords.push_back(u + u_inter);
			texcoords.push_back(v);
			// 2 top
			texcoords.push_back(u + u_inter);
			texcoords.push_back(v + v_inter);
			//// 2 top
			//texcoords.push_back(u + u_inter);
			//texcoords.push_back(v + v_inter);
			// 3 top
			texcoords.push_back(u);
			texcoords.push_back(v + v_inter);
			// 0 bottom
			texcoords.push_back(u);
			texcoords.push_back(v);

			// 0 bottom
			norms.push_back(disc_cos_n(x, radius, theta));
			norms.push_back(y0);
			norms.push_back(disc_sin_n(z, radius, theta));
			// 1 bottom
			norms.push_back(disc_cos_n(x, radius, theta + interval));
			norms.push_back(y0);
			norms.push_back(disc_sin_n(z, radius, theta + interval));
			// 2 top
			norms.push_back(disc_cos_n(x, radius, theta + interval));
			norms.push_back(y1);
			norms.push_back(disc_sin_n(z, radius, theta + interval));
			//// 2 top
			//norms.push_back(disc_cos_n(x, radius, theta + interval));
			//norms.push_back(y1);
			//norms.push_back(disc_sin_n(z, radius, theta + interval));
			// 3 top
			norms.push_back(disc_cos_n(x, radius, theta));
			norms.push_back(y1);
			norms.push_back(disc_sin_n(z, radius, theta));
			// 0 bottom
			norms.push_back(disc_cos_n(x, radius, theta));
			norms.push_back(y0);
			norms.push_back(disc_sin_n(z, radius, theta));

			theta += interval;
			u += u_inter;
		}
		v += v_inter;
		u = 0;
		theta = 0.0;
	}
}

void Shape::renderCylinder(GLuint *disc_texture, GLuint *side_texture) {
	// bottom disc
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//auto *p_verts = disc_verts.data();
	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, disc_verts.data());
	glNormalPointer(GL_FLOAT, 0, disc_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, disc_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *disc_texture);
	glDrawArrays(GL_TRIANGLE_FAN, 0, disc_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// top disc
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, disc1_verts.data());
	glNormalPointer(GL_FLOAT, 0, disc1_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, disc_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *disc_texture);
	glDrawArrays(GL_TRIANGLE_FAN, 0, disc1_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// side
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *side_texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::buildCone(float radius, float edges, float height, float x, float y, float z) {
	float 
		interval = 2.0 * M_PI / edges,
		diameter = 2 * radius,
		start = 0.0,
		theta = 0.0;

	for (int i = 0; i < edges; ++i) {
		// bottom disk
		cone_verts.push_back(x);
		cone_verts.push_back(y);
		cone_verts.push_back(z);
		cone_verts.push_back(x + radius * cos(theta));
		cone_verts.push_back(y);
		cone_verts.push_back(z + radius * sin(theta));
		cone_verts.push_back(x + radius * cos(theta + interval));
		cone_verts.push_back(y);
		cone_verts.push_back(z + radius * sin(theta + interval));
		// tip
		cone_verts.push_back(x);
		cone_verts.push_back(y + height);
		cone_verts.push_back(z);
		// bottom disk
		for (int i = 0; i < 3; ++i) {
			cone_norms.push_back(0);
			cone_norms.push_back(-1);
			cone_norms.push_back(0);
		} // TODO normals
		/*cone_norms.push_back((x) / radius);
		cone_norms.push_back((y) / radius);
		cone_norms.push_back((z) / radius);
		cone_norms.push_back((x + radius * cos(theta) / radius));
		cone_norms.push_back((y) / radius);
		cone_norms.push_back((z + radius * sin(theta)) / radius);
		cone_norms.push_back((x + radius * cos(theta + interval)) / radius);
		cone_norms.push_back((y) / radius);
		cone_norms.push_back((z + radius * sin(theta + interval)) / radius);*/
		// tip
		cone_norms.push_back((x) / radius);
		cone_norms.push_back((y + height) / radius);
		cone_norms.push_back((z) / radius);
		// bottom disk
		cone_texcoords.push_back(start + 0.5);
		cone_texcoords.push_back(start + 0.5);
		cone_texcoords.push_back(cos(theta) / diameter + 0.5);
		cone_texcoords.push_back(sin(theta) / diameter + 0.5);
		cone_texcoords.push_back(cos(theta) / diameter + 0.5);
		cone_texcoords.push_back(sin(theta) / diameter + 0.5);
		// tip
		cone_texcoords.push_back(start + 0.5);
		cone_texcoords.push_back(start + 0.5);

		theta += interval;
	}
}

void Shape::renderCone(GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, cone_verts.data());
	glNormalPointer(GL_FLOAT, 0, cone_norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, cone_texcoords.data());

	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, cone_verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
