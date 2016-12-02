#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4 Vector4::copy() {
	Vector4 copy(this->x,
				 this->y,
				 this->z,
				 this->w);

	return copy;
}

bool Vector4::equals(const Vector4& v2, float epsilon) {
	return ((fabsf(this->x - v2.x) < epsilon) &&
			(fabsf(this->y - v2.y) < epsilon) &&
			(fabsf(this->z - v2.z) < epsilon) &&
			(fabsf(this->w - v2.w) < epsilon));
}

bool Vector4::equals(const Vector4& v2) {
	return equals(v2, 0.00001f);
}


float Vector4::length() {
	return static_cast<float>(sqrt(this->lengthSquared()));
}

float Vector4::lengthSquared() {
	return (this->x*this->x +
			this->y*this->y +
			this->z*this->z +
			this->z*this->w	);
}

void Vector4::normalise() {
	float mag = this->length();
	if (mag) {
		float multiplier = 1.0f / mag;
		this->x *= multiplier;
		this->y *= multiplier;
		this->z *= multiplier;
		this->w *= multiplier;
	}
}

Vector4 Vector4::normalised() {
	Vector4 norm(x, y, z, w);
	norm.normalise();
	return norm;
}

Vector4 Vector4::cross(const Vector4& v2) {
	Vector4 cross(
		(this->x * v2.y - this->y * v2.x),
		(this->y * v2.z - this->z * v2.y),
		(this->z * v2.x - this->x * v2.z),
		(this->w * v2.w - this->w * v2.w)
		);
	return cross;
}

void Vector4::subtract(const Vector4& v1, float scale) {
	this->x -= ((v1.x) * scale);
	this->y -= ((v1.y) * scale);
	this->z -= ((v1.z) * scale);
	this->w -= ((v1.w) * scale);
}

void Vector4::set(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vector4::set(float translate[4]) {
	this->x = translate[0];
	this->y = translate[1];
	this->z = translate[2];
	this->w = translate[3];
}

void Vector4::setX(float x) {
	this->x = x;
}

void Vector4::setY(float y) {
	this->y = y;
}

void Vector4::setZ(float z) {
	this->z = z;
}

void Vector4::setW(float w) {
	this->w = w;
}

float Vector4::getX() {
	return this->x;
}

float Vector4::getY() {
	return this->y;
}

float Vector4::getZ() {
	return this->z;
}

float Vector4::getW() {
	return this->w;
}

float Vector4::dot(const Vector4& v2) {
	return (this->x*v2.x +
		this->y*(v2.y) +
		this->z*(v2.z) +
		this->w*(v2.w)
		);
}

void Vector4::scale(float scale) {
	((this->x) * scale);
	((this->y) * scale);
	((this->z) * scale);
	((this->w) * scale);
}

void Vector4::add(const Vector4& v1, float scale) {
	this->x += ((v1.x) * scale);
	this->y += ((v1.y) * scale);
	this->z += ((v1.z) * scale);
	this->w += ((v1.w) * scale);
}

Vector4 Vector4::operator+(const Vector4& v2) {
	return Vector4(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

Vector4 Vector4::operator-(const Vector4& v2) {
	return Vector4(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

Vector4& Vector4::operator+=(const Vector4& v2) {
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v2) {
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;
	return *this;
}

void Vector4::operator=(const Vector4& v2) {
	this->x = v2.x;
	this->y = v2.y;
	this->z = v2.z;
}

void Vector4::operator=(float* array) {
	this->x = array[0];
	this->y = array[1];
	this->z = array[2];
}
