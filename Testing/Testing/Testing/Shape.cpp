#include "Shape.h"



Shape::Shape()
{
}


Shape::~Shape()
{
}

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
	return (cos(theta) * sin(delta)) / radius;
}
float Shape::calc_n_y0(float radius, float theta, float delta) {
	return cos(delta) / radius;
}
float Shape::calc_n_z0(float radius, float theta, float delta) {
	return (sin(theta) * sin(delta)) / radius;
}

float Shape::calc_n_x1(float radius, float theta, float delta, float delta_interval) {
	return (cos(theta) * sin(delta + delta_interval)) / radius;
}
float Shape::calc_n_y1(float radius, float theta, float delta, float delta_interval) {
	return (cos(delta + delta_interval)) / radius;
}
float Shape::calc_n_z1(float radius, float theta, float delta, float delta_interval) {
	return (sin(theta) * sin(delta + delta_interval)) / radius;
}

float Shape::calc_n_x2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return (cos(theta + theta_interval) * sin(delta + delta_interval)) / radius;
}
float Shape::calc_n_y2(float radius, float theta, float delta, float delta_interval) {
	return (cos(delta + delta_interval)) / radius;
}
float Shape::calc_n_z2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return (sin(theta + theta_interval) * sin(delta + delta_interval)) / radius;
}

float Shape::calc_n_x3(float radius, float theta, float delta, float theta_interval) {
	return (cos(theta + theta_interval) * sin(delta)) / radius;
}
float Shape::calc_n_y3(float radius, float theta, float delta, float theta_interval) {
	return cos(delta) / radius;
}
float Shape::calc_n_z3(float radius, float theta, float delta, float theta_interval) {
	return (sin(theta + theta_interval) * sin(delta)) / radius;
}

void Shape::drawSphere(double radius, double latitude, double longitude) {
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
				double x0 = calc_x0(radius, theta, delta);
				cout << x0 << endl;
				double
					y0 = calc_y0(radius, theta, delta),
					z0 = calc_z0(radius, theta, delta),
					n_x0 = calc_n_x0(radius, theta, delta),
					n_y0 = calc_n_y0(radius, theta, delta),
					n_z0 = calc_n_z0(radius, theta, delta),
					v0 = u_lats,
					u0 = v_longs,

					x1 = calc_x1(radius, theta, delta, delta_interval),
					y1 = calc_y1(radius, theta, delta, delta_interval),
					z1 = calc_z1(radius, theta, delta, delta_interval),
					n_x1 = calc_n_x1(radius, theta, delta, delta_interval),
					n_y1 = calc_n_y1(radius, theta, delta, delta_interval),
					n_z1 = calc_n_z1(radius, theta, delta, delta_interval),
					v1 = u_lats + u_lats_interval,
					u1 = v_longs,

					x2 = calc_x2(radius, theta, theta_interval, delta, delta_interval),
					y2 = calc_y2(radius, theta, delta, delta_interval),
					z2 = calc_z2(radius, theta, theta_interval, delta, delta_interval),
					n_x2 = calc_n_x2(radius, theta, delta, delta_interval, theta_interval),
					n_y2 = calc_n_y2(radius, theta, delta, delta_interval),
					n_z2 = calc_n_z2(radius, theta, delta, delta_interval, theta_interval),
					v2 = u_lats + u_lats_interval,
					u2 = v_longs + v_longs_interval,

					x3 = calc_x3(radius, theta, theta_interval, delta),
					y3 = calc_y3(radius, theta, theta_interval, delta),
					z3 = calc_z3(radius, theta, theta_interval, delta),
					n_x3 = calc_n_x3(radius, theta, delta, theta_interval),
					n_y3 = calc_n_y3(radius, theta, delta, theta_interval),
					n_z3 = calc_n_z3(radius, theta, delta, theta_interval),
					v3 = u_lats,
					u3 = v_longs + v_longs_interval;

					theta += theta_interval;
					v_longs += v_longs_interval;
			}
			u_lats += u_lats_interval;
			theta = 0.0; v_longs = 0.0;
			delta += delta_interval;
		}
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
			vertices_sphere.push_back((int)(calc_n_x0(radius, theta, delta) / calc_x0(radius, theta, delta)));
			vertices_sphere.push_back((int)(calc_n_y0(radius, theta, delta) / calc_y0(radius, theta, delta)));
			vertices_sphere.push_back((int)(calc_n_z0(radius, theta, delta) / calc_z0(radius, theta, delta)));

			vertices_sphere.push_back((int)(calc_n_x1(radius, theta, delta, delta_interval) / calc_x1(radius, theta, delta, delta_interval)));
			vertices_sphere.push_back((int)(calc_n_y1(radius, theta, delta, delta_interval) / calc_y1(radius, theta, delta, delta_interval)));
			vertices_sphere.push_back((int)(calc_n_z1(radius, theta, delta, delta_interval) / calc_z1(radius, theta, delta, delta_interval)));

			vertices_sphere.push_back((int)(calc_n_x2(radius, theta, theta_interval, delta, delta_interval) / calc_x2(radius, theta, theta_interval, delta, delta_interval)));
			vertices_sphere.push_back((int)(calc_n_y2(radius, theta, delta, delta_interval) / calc_y2(radius, theta, delta, delta_interval)));
			vertices_sphere.push_back((int)(calc_n_z2(radius, theta, theta_interval, delta, delta_interval) / calc_z2(radius, theta, theta_interval, delta, delta_interval)));

			vertices_sphere.push_back((int)(calc_n_x2(radius, theta, theta_interval, delta, delta_interval) / calc_x2(radius, theta, theta_interval, delta, delta_interval)));
			vertices_sphere.push_back((int)(calc_n_y2(radius, theta, delta, delta_interval) / calc_y2(radius, theta, delta, delta_interval)));
			vertices_sphere.push_back((int)(calc_n_z2(radius, theta, theta_interval, delta, delta_interval) / calc_z2(radius, theta, theta_interval, delta, delta_interval)));

			vertices_sphere.push_back((int)(calc_n_x3(radius, theta, theta_interval, delta) / calc_x3(radius, theta, theta_interval, delta)));
			vertices_sphere.push_back((int)(calc_n_y3(radius, theta, theta_interval, delta) / calc_y3(radius, theta, theta_interval, delta)));
			vertices_sphere.push_back((int)(calc_n_z3(radius, theta, theta_interval, delta) / calc_z3(radius, theta, theta_interval, delta)));

			vertices_sphere.push_back((int)(calc_n_x0(radius, theta, delta) / calc_x0(radius, theta, delta)));
			vertices_sphere.push_back((int)(calc_n_y0(radius, theta, delta) / calc_y0(radius, theta, delta)));
			vertices_sphere.push_back((int)(calc_n_z0(radius, theta, delta) / calc_z0(radius, theta, delta)));

			normals_sphere.push_back(calc_n_x0(radius, theta, delta));
			normals_sphere.push_back(calc_n_y0(radius, theta, delta));
			normals_sphere.push_back(calc_n_z0(radius, theta, delta));

			normals_sphere.push_back(calc_n_x1(radius, theta, delta, delta_interval));
			normals_sphere.push_back(calc_n_y1(radius, theta, delta, delta_interval));
			normals_sphere.push_back(calc_n_z1(radius, theta, delta, delta_interval));

			normals_sphere.push_back(calc_n_x2(radius, theta, delta, delta_interval, theta_interval));
			normals_sphere.push_back(calc_n_y2(radius, theta, delta, delta_interval));
			normals_sphere.push_back(calc_n_z2(radius, theta, delta, delta_interval, theta_interval));

			normals_sphere.push_back(calc_n_x3(radius, theta, delta, theta_interval));
			normals_sphere.push_back(calc_n_y3(radius, theta, delta, theta_interval));
			normals_sphere.push_back(calc_n_z3(radius, theta, delta, theta_interval));

			texcoords_sphere.push_back(u_lats);
			texcoords_sphere.push_back(v_longs);

			texcoords_sphere.push_back(u_lats + u_lats_interval);
			texcoords_sphere.push_back(v_longs);

			texcoords_sphere.push_back(u_lats + u_lats_interval);
			texcoords_sphere.push_back(v_longs + v_longs_interval);

			texcoords_sphere.push_back(u_lats);
			texcoords_sphere.push_back(v_longs + v_longs_interval);

			theta += theta_interval;
			v_longs += v_longs_interval;
		}
		u_lats += u_lats_interval;
		theta = 0.0; v_longs = 0.0;
		delta += delta_interval;
	}
}


