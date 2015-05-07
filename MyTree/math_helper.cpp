/************************************\
| a little math class for opengl     |
\************************************/

#include "math_helper.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

vec2::vec2()
{

}

vec2::vec2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

vec3::vec3 () {}

vec3::vec3 (float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

vec3::vec3(const vec2 &_v, float z)
{
	v[0] = _v.v[0];
	v[1] = _v.v[1];
	v[2] = z;
}

vec4::vec4 () {}

vec4::vec4 (float x, float y, float z, float w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

vec4::vec4 (const vec2& _v, float z, float w) {
	v[0] = _v.v[0];
	v[1] = _v.v[1];
	v[2] = z;
	v[3] = w;
}

vec4::vec4 (const vec3& _v, float w) {
	v[0] = _v.v[0];
	v[1] = _v.v[1];
	v[2] = _v.v[2];
	v[3] = w;
}

mat3::mat3()
{

}

mat3::mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i) 
{
	m[0] = a;
	m[1] = b;
	m[2] = c;
	m[3] = d;
	m[4] = e;
	m[5] = f;
	m[6] = g;
	m[7] = h;
	m[8] = i;
}

mat4::mat4 (float a, float b, float c, float d,
						float e, float f, float g, float h,
						float i, float j, float k, float l,
						float _m, float n, float o, float p) {
	m[0] = a;
	m[1] = b;
	m[2] = c;
	m[3] = d;
	m[4] = e;
	m[5] = f;
	m[6] = g;
	m[7] = h;
	m[8] = i;
	m[9] = j;
	m[10] = k;
	m[11] = l;
	m[12] = _m;
	m[13] = n;
	m[14] = o;
	m[15] = p;
}
mat4 identityMat4()
{
	return mat4 (
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void print (const vec2& v) {
	printf ("[%.2f, %.2f]\n", v.v[0], v.v[1]);
}

void print (const vec3& v) {
	printf ("[%.2f, %.2f, %.2f]\n", v.v[0], v.v[1], v.v[2]);
}

void print (const vec4& v) {
	printf ("[%.2f, %.2f, %.2f, %.2f]\n", v.v[0], v.v[1], v.v[2], v.v[3]);
}

void print (const mat3& m) {
	printf("\n");
	printf ("[%.2f][%.2f][%.2f]\n", m.m[0], m.m[3], m.m[6]);
	printf ("[%.2f][%.2f][%.2f]\n", m.m[1], m.m[4], m.m[7]);
	printf ("[%.2f][%.2f][%.2f]\n", m.m[2], m.m[5], m.m[8]);
}

void print (const mat4& m) {
	printf("\n");
	printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[0], m.m[4], m.m[8], m.m[12]);
	printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[1], m.m[5], m.m[9], m.m[13]);
	printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[2], m.m[6], m.m[10], m.m[14]);
	printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[3], m.m[7], m.m[11], m.m[15]);
}

float length(const vec3& v)
{
	return sqrt(v.v[0] *v.v[0] + v.v[1]* v.v[1] + v.v[2]*v.v[2]);
}

float length2(const vec3& v)
{
	return (v.v[0] *v.v[0] + v.v[1]* v.v[1] + v.v[2]*v.v[2]);
}

vec3 normalise(const vec3& v)
{
	vec3 tmpvec;
	float len = length(v);
	if(len == 0.0f)
		return vec3(0.0f,0.0f,0.0f);

	tmpvec.v[0] = v.v[0] / len;
	tmpvec.v[1] = v.v[1] / len;
	tmpvec.v[2] = v.v[2] / len;

	return tmpvec;
}

vec3 vec3::operator+(const vec3& rhs)
{
	vec3 tmpvec;
	tmpvec.v[0] = v[0] + rhs.v[0];
	tmpvec.v[1] = v[1] + rhs.v[1];
	tmpvec.v[2] = v[2] + rhs.v[2];
	return tmpvec;
}

vec3& vec3::operator+=(const vec3& rhs)
{
	v[0] += rhs.v[0];
	v[1] += rhs.v[1];
	v[2] += rhs.v[2];

	return *this;
}
vec3 vec3::operator-(const vec3& rhs)
{
	vec3 tmpvec;

	tmpvec.v[0] = v[0] - rhs.v[0];
	tmpvec.v[1] = v[1] - rhs.v[1];
	tmpvec.v[2] = v[2] - rhs.v[2];

	return tmpvec;
}

vec3& vec3::operator-=(const vec3& rhs)
{
	v[0] -= rhs.v[0];
	v[1] -= rhs.v[1];
	v[2] -= rhs.v[2];

	return *this;
}

vec3 vec3::operator*(float rhs)
{
	vec3 tmpvec;

	tmpvec.v[0] = v[0] * rhs;
	tmpvec.v[1] = v[1] * rhs;
	tmpvec.v[2] = v[2] * rhs;

	return tmpvec;
}

vec3& vec3::operator=(const vec3& rhs)
{
	if(this == &rhs)
		return *this;

	v[0] = rhs.v[0];
	v[1] = rhs.v[1];
	v[2] = rhs.v[2];

	return *this;
}

vec4 mat4::operator*(const vec4& rhs)
{
	vec4 tmpvec;

	tmpvec.v[0] = m[0] * rhs.v[0] + m[4] * rhs.v[1] + m[8] * rhs.v[2] + m[12] * rhs.v[3];
	tmpvec.v[1] = m[1] * rhs.v[0] + m[5] * rhs.v[1] + m[9] * rhs.v[2] + m[13] * rhs.v[3];
	tmpvec.v[2] = m[2] * rhs.v[0] + m[6] * rhs.v[1] + m[10] * rhs.v[2] + m[14] * rhs.v[3];
	tmpvec.v[0] = m[3] * rhs.v[0] + m[7] * rhs.v[1] + m[11] * rhs.v[2] + m[15] * rhs.v[3];

	return tmpvec;
}

mat4 mat4::operator*(const mat4& rhs)
{
	mat4 tmpmat(0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
	int r_index = 0;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			float sum = 0.0f;
			for (int i = 0; i < 4; i++) {
				sum += rhs.m[i + col * 4] * m[row + i * 4];
			}
			tmpmat.m[r_index] = sum;
			r_index++;
		}
	}
	return tmpmat;
}

mat4& mat4::operator= (const mat4& rhs) {
	for (int i = 0; i < 16; i++) {
		m[i] = rhs.m[i];
	}
	return *this;
}



float dot (const vec3& a, const vec3& b)
{
	return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}

vec3 cross (const vec3& a, const vec3& b)
{
	vec3 tmpvec;
	tmpvec.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
	tmpvec.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
	tmpvec.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];

	return tmpvec;
}

mat4 transpose (const mat4& mm)
{
	return mat4 (
		mm.m[0], mm.m[4], mm.m[8], mm.m[12],
		mm.m[1], mm.m[5], mm.m[9], mm.m[13],
		mm.m[2], mm.m[6], mm.m[10], mm.m[14],
		mm.m[3], mm.m[7], mm.m[11], mm.m[15]
	);
}

mat4 translate(const mat4& mm, const vec3& v)
{
	mat4 tmpmat = identityMat4();
	tmpmat.m[12] = v.v[0];
	tmpmat.m[13] = v.v[1];
	tmpmat.m[14] = v.v[2];
	return tmpmat * mm;
}

mat4 rotateYbyDEG(const mat4& mm, float degree)
{
	float rad = degree * DEGREE_IN_RAD;
	mat4 tmpmat = identityMat4();
	tmpmat.m[0] = cos(rad);
	tmpmat.m[8] = sin(rad);
	tmpmat.m[2] = -sin(rad);
	tmpmat.m[10] = cos(rad);

	return tmpmat*mm;
}