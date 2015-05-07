/***********************************************************\
| Helperclass for math										|
| First Version												|
\***********************************************************/

#define DEGREE_IN_RAD (2.0 * M_PI)/ 360.0;
#define RADIAN_IN_DEGREE 360.0 *(2.0*M_PI);


struct vec2;
struct vec3;
struct vec4;

struct vec2 {
	vec2();
	vec2(float x, float y);
	float v[2];
};

struct vec3{
	vec3();
	vec3(float x, float y, float z);
	vec3(const vec2 &_v, float z);
	vec3 operator+(float rhs);
	vec3 operator+(const vec3& rhs);
	vec3& operator+=(const vec3& rhs);
	vec3 operator-(const vec3& rhs);
	vec3& operator-=(const vec3& rhs);
	vec3 operator*(float rhs);
	vec3& operator*=(const vec3& rhs);
	vec3& operator=(const vec3& rhs);

	float v[3];
};

struct vec4 {
	vec4 ();
	vec4 (float x, float y, float z, float w);
	vec4 (const vec2& _v, float z, float w);
	vec4 (const vec3& _v, float w);
	float v[4];
};

struct mat3{
	mat3();
	mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	float m[9];
};

struct mat4{
	mat4();
	mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i,float j, float k, float l,
				float _m, float n, float o, float p);
	vec4 operator*(const vec4& rhs);
	mat4 operator*(const mat4& rhs);
	mat4& operator=(const mat4& rhs);
	float m[16];
};

/*******************************************\
| some functions							|
\*******************************************/

void print (const vec2& v);
void print (const vec3& v);
void print (const vec4& v);
void print (const mat3& m);
void print (const mat4& m);

float length (const vec3& v);
float length2 (const vec3& v);
vec3 normalise (const vec3& v);
float dot (const vec3& a, const vec3& b);
vec3 cross (const vec3& a, const vec3& b);

mat4 transpose (const mat4& mm);
mat4 identityMat4();
mat4 translate(const mat4& mm, const vec3& v);
mat4 rotateYbyDEG(const mat4& mm, float degree);
