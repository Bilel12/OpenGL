// Based on Vector4 class made by Paul Robertson
#ifndef _VECTOR4_H
#define _VECTOR4_H

#include <math.h>

class Vector4 {

public:
	Vector4(float x = 0, float y = 0, float z = 0, float w = 0);
	Vector4 copy();


	void set(float x, float y, float z, float w);
	void set(float translate[3]);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);

	float getX();
	float getY();
	float getZ();
	float getW();

	void add(const Vector4& v1, float scale = 1.0);
	void subtract(const Vector4& v1, float scale = 1.0);
	void scale(float scale);

	float dot(const Vector4& v2);
	Vector4 cross(const Vector4& v2);

	void normalise();
	Vector4 normalised();
	float length();
	float lengthSquared();

	bool equals(const Vector4& v2, float epsilon);
	bool equals(const Vector4& v2);

	Vector4 operator+(const Vector4& v2);
	Vector4 operator-(const Vector4& v2);
	void operator=(const Vector4& v2);
	void operator=(float* array);

	Vector4& operator+=(const Vector4& v2);
	Vector4& operator-=(const Vector4& v2);

	float x;
	float y;
	float z;
	float w;
};

#endif // !_VECTOR4_H
