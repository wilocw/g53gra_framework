#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
// scales a vector a by float scale
// a = a*scale
// result stored in a
inline void scale(float* a, const float& scale)
{
	for (int i = 0; i < 3; i++, a++)
		*a = *a*scale;
}

// Adds vector b * scale to vector a
// a = a + (b*scale)
// Result is stored in vector a
inline void add(float* a, const float* b, const float& scale = 1.0f)
{
	for (int i = 0; i < 3; i++)
		*a++ += scale * (*b++);
}

// subtracts vector b * scale from vector a
// a = a - (b*scale)
// Result is stored in vector a
inline void sub(float* a, const float* b, const float& scale = 1.0f)
{
	for (int i = 0; i < 3; i++)
		*a++ -= scale * (*b++);
}

// normalises a vector n
// n = n / sqrt(x^2 + y^2 + z^2)
// Result stored in vector n
inline void norm(float* n)
{
	float l = 0.0f;

	for (int i = 0; i < 3; i++)
		l += n[i] * n[i];

	l = sqrt(l);

	for (int i = 0; i < 3; i++)
		n[i] /= l;
}

// cross product of vector a and vector b sets  vector c to be the result
// c = a X b
// result stored in vector c
inline void cross(const float* a, const float* b, float* c)
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

// dot product between vector a and vector b, set the result to float dot
// dot = a.b;
// result stored in float dot
inline void dot(const float* a, const float* b, float& dot)
{
	dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}