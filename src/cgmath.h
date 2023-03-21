/***************************************************
 * NOTE:
 * (1) Implementation
 * "cgmath.h" works like stb headers library. 
 * You need to create an implementation in a c/c++ file.
 * After an implementation made in one file, 
 * you include "cgmath.h" as an ordinary header file
 *
 * Do this to create an implementation:
 * ```c
 * #define CGMATH_IMPLEMENTATION
 * #include "cgmath.h"
 * ```
 * For example your implementation file will look like this:
 * ```c
 * #include <stdio.h>
 * #include <stdlib.h>
 * #define CGMATH_IMPLEMENTATION
 * #include "cgmath.h"
 * ```
 * 
 * (2) Platform
 * If you are working on linux or other posix platform
 * You will need to link with the math library
 * 
 ***************************************************/

#ifndef __CGMATH_H__
#define __CGMATH_H__

#define CGMATH_PI 3.14159265358979323846f
#define CGMATH_PI_2 2.0f * CGMATH_PI
#define CGMATH_HALF_PI 0.5f * CGMATH_PI
#define CGMATH_QUARTER_PI 0.25f * CGMATH_PI
#define CGMATH_ONE_OVER_PI 1.0f / CGMATH_PI
#define CGMATH_ONE_OVER_TWO_PI 1.0f / CGMATH_PI_2
#define CGMATH_SQRT_TWO 1.41421356237309504880f
#define CGMATH_SQRT_THREE 1.73205080756887729352f
#define CGMATH_SQRT_ONE_OVER_TWO 0.70710678118654752440f
#define CGMATH_SQRT_ONE_OVER_THREE 0.57735026918962576450f
#define CGMATH_DEG2RAD_MULTIPLIER CGMATH_PI / 180.0f
#define CGMATH_RAD2DEG_MULTIPLIER 180.0f / CGMATH_PI
#define CGMATH_SEC_TO_US_MULTIPLIER (1000.0f * 1000.0f)
#define CGMATH_SEC_TO_MS_MULTIPLIER 1000.0f
#define CGMATH_MS_TO_SEC_MULTIPLIER 0.001f
#define CGMATH_INFINITY 1e30f
#define CGMATH_FLOAT_EPSILON 1.192092896e-07f

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef union vec2 {
	float Elements[2];
	struct {
		union {
			float x, r, s, u;
		};
		union {
			float y, g, t, v;
		};
	};
} vec2_t;

typedef union vec3 {
	float Elements[3];
	struct {
		union {
			float x, r, s, u;
		};
		union {
			float y, g, t, v;
		};
		union {
			float z, b, p, w;
		};
	};
} vec3_t;

typedef union vec4 {
	float Elements[4];
	struct {
		union {
			float x, r, s;
		};
		union {
			float y, g, t;
		};
		union {
			float z, b, p;
		};
		union {
			float w, a, q;
		};
	};
} vec4_t;

typedef union mat4 {
	vec4_t Rows[4];
	float Elements[16];
} mat4_t;

vec2_t 	vec2(float x, float y);
vec2_t 	vec2_zeros();
vec2_t 	vec2_ones();
vec2_t 	vec2_add(vec2_t a, vec2_t b);
vec2_t 	vec2_sub(vec2_t a, vec2_t b);
vec2_t 	vec2_mul(vec2_t a, vec2_t b);
vec2_t 	vec2_div(vec2_t a, vec2_t b);
float  	vec2_length(vec2_t a);
void	vec2_normalize(vec2_t* a);
bool 	vec2_compare(vec2_t a, vec2_t b);
float 	vec2_distance(vec2_t a, vec2_t b);

vec3_t 	vec3(float x, float y, float z);
vec3_t 	vec3_zeros();
vec3_t 	vec3_ones();
vec3_t 	vec3_add(vec3_t a, vec3_t b);
vec3_t 	vec3_sub(vec3_t a, vec3_t b);
vec3_t 	vec3_mul(vec3_t a, vec3_t b);
vec3_t 	vec3_div(vec3_t a, vec3_t b);
float	vec3_dot(vec3_t a, vec3_t b);
float  	vec3_length(vec3_t a);
void	vec3_normalize(vec3_t* a);
vec3_t 	vec3_normalized(vec3_t a);
bool 	vec3_compare(vec3_t a, vec3_t b);
float 	vec3_distance(vec3_t a, vec3_t b);
vec3_t 	vec3_cross(vec3_t a, vec3_t b);

vec4_t 	vec4(float x, float y, float z, float w);
vec4_t 	vec4_zeros();
vec4_t 	vec4_ones();
vec4_t 	vec4_add(vec4_t a, vec4_t b);
vec4_t 	vec4_sub(vec4_t a, vec4_t b);
vec4_t 	vec4_mul(vec4_t a, vec4_t b);
vec4_t 	vec4_div(vec4_t a, vec4_t b);
float	vec4_dot(vec4_t a, vec4_t b);
float  	vec4_length(vec4_t a);
void	vec4_normalize(vec4_t* a);

mat4_t mat4(float a);
mat4_t mat4_identity();
mat4_t mat4_add(mat4_t a, mat4_t b);
mat4_t mat4_sub(mat4_t a, mat4_t b);
mat4_t mat4_mul(mat4_t a, mat4_t b);
mat4_t mat4_div(mat4_t a, mat4_t b);
mat4_t mat4_dot(mat4_t a, mat4_t b);
mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far);
mat4_t mat4_perspective(float fov_radians, float aspect_ratio, float near, float far);
mat4_t Mat4_look_at(vec3_t pos, vec3_t target, vec3_t up);
mat4_t mat4_inverse(mat4_t matrix);
mat4_t mat4_translation(vec3_t position);
mat4_t mat4_scale(vec3_t scale);
mat4_t mat4_transpose(mat4_t matrix);
mat4_t mat4_euler_x(float angle_radians);
mat4_t mat4_euler_y(float angle_radians);
mat4_t mat4_euler_z(float angle_radians);
mat4_t mat4_euler_xyz(float x_radians, float y_radians, float z_radians);


#ifdef CGMATH_IMPLEMENTATION

// vec2
vec2_t vec2(float x, float y) {
	vec2_t res = {0};
	res.x = x;
	res.y = y;
	return res;
}

vec2_t vec2_zeros() {
	return vec2(0.0f, 0.0f);
}

vec2_t vec2_ones() {
	return vec2(1.0f, 1.0f);
}

vec2_t vec2_add(vec2_t a, vec2_t b) {
	return vec2(
		a.x + b.x,
		a.y + b.y
	);
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
	return vec2(
		a.x - b.x,
		a.y - b.y
	);
}
vec2_t vec2_mul(vec2_t a, vec2_t b) {
	return vec2(
		a.x * b.x,
		a.y * b.y
	);
}

vec2_t vec2_div(vec2_t a, vec2_t b) {
	return vec2(
		a.x / b.x,
		a.y / b.y
	);
}

float vec2_length(vec2_t a) {
	return sqrtf( a.x * a.x + a.y * a.y );
}

void vec2_normalize(vec2_t* a) {
	const float length = vec2_length(*a);
	a->x /= length;
	a->y /= length;
}

bool vec2_compare(vec2_t a, vec2_t b) {
	if(fabsf(a.x - b.x) > CGMATH_FLOAT_EPSILON) return false;
	if(fabsf(a.y - b.y) > CGMATH_FLOAT_EPSILON) return false;
	return true;
}

float vec2_distance(vec2_t a, vec2_t b) {
	vec2_t d = vec2(a.x - b.x, a.y - b.y);
	return vec2_length(d);
}

// vec3
vec3_t vec3(float x, float y, float z) {
	vec3_t res = {0};
	res.x = x;
	res.y = y;
	res.z = z;
	return res;
}

vec3_t vec3_zeros() {
	return vec3(0.0f, 0.0f, 0.0f);
}

vec3_t vec3_ones() {
	return vec3(1.0f, 1.0f, 1.0f);
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
	return vec3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
	return vec3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

vec3_t vec3_mul(vec3_t a, vec3_t b) {
	return vec3(
		a.x * b.x,
		a.y * b.y,
		a.z * b.z
	);
}

vec3_t vec3_div(vec3_t a, vec3_t b) {
	return vec3(
		a.x / b.x,
		a.y / b.y,
		a.z / b.z
	);
}

float vec3_dot(vec3_t a, vec3_t b) {
	float p = 0;
	p += a.x * b.x;
	p += a.y * b.y;
	p += a.z * b.z;
	return p;
}

float vec3_length(vec3_t a) {
	return sqrtf( a.x * a.x + a.y * a.y + a.z * a.z );
}

void vec3_normalize(vec3_t* a) {
	const float length = vec3_length(*a);
    a->x /= length;
    a->y /= length;
    a->z /= length;
}

vec3_t vec3_normalized(vec3_t a) {
	vec3_normalize(&a);
	return a;
}

bool vec3_compare(vec3_t a, vec3_t b) {
    if(fabsf(a.x - b.x) > CGMATH_FLOAT_EPSILON) return false;
    if(fabsf(a.y - b.y) > CGMATH_FLOAT_EPSILON) return false;
    if(fabsf(a.z - b.z) > CGMATH_FLOAT_EPSILON) return false;
    return true;
}

float vec3_distance(vec3_t a, vec3_t b) {
	vec3_t d = vec3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
	return vec3_length(d);
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
	return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

// vec4
vec4_t vec4(float x, float y, float z, float w) {
	vec4_t res = {0};
	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return res;
}

vec4_t vec4_zeros() {
	return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

vec4_t vec4_ones() {
	return vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

vec4_t vec4_add(vec4_t a, vec4_t b) {
	return vec4(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
	);
}

vec4_t vec4_sub(vec4_t a, vec4_t b) {
	return vec4(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
	);
}

vec4_t vec4_mul(vec4_t a, vec4_t b) {
	return vec4(
		a.x * b.x,
		a.y * b.y,
		a.z * b.z,
		a.w * b.w
	);
}

vec4_t vec4_div(vec4_t a, vec4_t b) {
	return vec4(
		a.x / b.x,
		a.y / b.y,
		a.z / b.z,
		a.w / b.w
	);
}

float vec4_dot(vec4_t a, vec4_t b) {
    float p = 0;
    p += a.x * b.x;
    p += a.y * b.y;
    p += a.z * b.z;
    p += a.w * b.w;
    return p;
}

float vec4_length(vec4_t a) {
	return sqrtf( a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w );	
}

void vec4_normalize(vec4_t* a) {
	const float length = vec4_length(*a);
    a->x /= length;
    a->y /= length;
    a->z /= length;
	a->w /= length;
}

// mat4
mat4_t mat4(float a) {
	mat4_t res = {0};
	for(int i = 0; i < 16; ++i) {
		res.Elements[i] = a;
	}
	return res;
}
mat4_t mat4_identity() {
	mat4_t res = {0};
	res.Elements[0] = 1.0f;
	res.Elements[5] = 1.0f;
	res.Elements[10] = 1.0f;
	res.Elements[15] = 1.0f;
	return res;
}

mat4_t mat4_add(mat4_t a, mat4_t b) {
	mat4_t res = {0};
	for(int i = 0; i < 16; i++) {
		res.Elements[i] = a.Elements[i] + b.Elements[i];
	}
	return res;
}

mat4_t mat4_sub(mat4_t a, mat4_t b) {
	mat4_t res = {0};
	for(int i = 0; i < 16; i++) {
		res.Elements[i] = a.Elements[i] - b.Elements[i];
	}
	return res;
}

mat4_t mat4_mul(mat4_t a, mat4_t b) {
	mat4_t res = {0};
	for(int i = 0; i < 16; i++) {
		res.Elements[i] = a.Elements[i] * b.Elements[i];
	}
	return res;
}

mat4_t mat4_div(mat4_t a, mat4_t b) {
	mat4_t res = {0};
	for(int i = 0; i < 16; i++) {
		res.Elements[i] = a.Elements[i] / b.Elements[i];
	}
	return res;
}

mat4_t mat4_dot(mat4_t a, mat4_t b) {
	mat4_t res = mat4_identity();
    const float* a_ptr = a.Elements;
    const float* b_ptr = b.Elements;
    float* dst_ptr = res.Elements;

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            *dst_ptr = 
                a_ptr[0] * b_ptr[0 + j] +
                a_ptr[1] * b_ptr[4 + j] +
                a_ptr[2] * b_ptr[8 + j] +
                a_ptr[3] * b_ptr[12 + j];
            dst_ptr++;
        }
        b_ptr += 4;
    }
    return res;
}

mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4_t res = mat4_identity();
    float lr = 1.0f / (left - right);
    float bt = 1.0f / (bottom - top);
    float nf = 1.0f / (near - far);

    res.Elements[0] = -2.0f * lr;
    res.Elements[5] = -2.0f * bt;
    res.Elements[10] = 2.0f * nf;

    res.Elements[12] = (left + right) * lr;
    res.Elements[13] = (top + bottom) * bt;
    res.Elements[14] = (near + far) * nf;	

    return res;
}

mat4_t mat4_perspective(float fov_radians, float aspect_ratio, float near, float far) {
	float half_tan_fov = tan(fov_radians * 0.5f);
	mat4_t res = mat4(0);
	res.Elements[0] = 1.0f / (aspect_ratio * half_tan_fov);
	res.Elements[5] = 1.0f / half_tan_fov;
	res.Elements[10] = -((far + near) / (far - near));
	res.Elements[11] = -1.0f;
	res.Elements[14] = -((2.0f * far * near) / (far - near));	
	return res;
}

mat4_t Mat4_look_at(vec3_t pos, vec3_t target, vec3_t up) {
	mat4_t result;
	vec3_t z_axis;
	z_axis.x = target.x - pos.x;
	z_axis.y = target.y - pos.y;
	z_axis.z = target.z - pos.z;

	z_axis = vec3_normalized(z_axis);
	vec3_t x_axis = vec3_normalized(vec3_cross(z_axis, up));
	vec3_t y_axis = vec3_cross(x_axis, z_axis);

	result.Elements[0] = x_axis.x;
	result.Elements[1] = y_axis.x;
	result.Elements[2] = -z_axis.x;
	result.Elements[3] = 0;
	result.Elements[4] = x_axis.y;
	result.Elements[5] = y_axis.y;
	result.Elements[6] = -z_axis.y;
	result.Elements[7] = 0;
	result.Elements[8] = x_axis.z;
	result.Elements[9] = y_axis.z;
	result.Elements[10] = -z_axis.z;
	result.Elements[11] = 0;
	result.Elements[12] = -vec3_dot(x_axis, pos);
	result.Elements[13] = -vec3_dot(y_axis, pos);
	result.Elements[14] = vec3_dot(z_axis, pos);
	result.Elements[15] = 1.0f;

	return result;	
}

mat4_t mat4_inverse(mat4_t matrix) {
	const float* m = matrix.Elements;

    float t0 = m[10] * m[15];
    float t1 = m[14] * m[11];
    float t2 = m[6] * m[15];
    float t3 = m[14] * m[7];
    float t4 = m[6] * m[11];
    float t5 = m[10] * m[7];
    float t6 = m[2] * m[15];
    float t7 = m[14] * m[3];
    float t8 = m[2] * m[11];
    float t9 = m[10] * m[3];
    float t10 = m[2] * m[7];
    float t11 = m[6] * m[3];
    float t12 = m[8] * m[13];
    float t13 = m[12] * m[9];
    float t14 = m[4] * m[13];
    float t15 = m[12] * m[5];
    float t16 = m[4] * m[9];
    float t17 = m[8] * m[5];
    float t18 = m[0] * m[13];
    float t19 = m[12] * m[1];
    float t20 = m[0] * m[9];
    float t21 = m[8] * m[1];
    float t22 = m[0] * m[5];
    float t23 = m[4] * m[1];

    mat4_t result;
    float* o = result.Elements;

    o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
    o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
    o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
    o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

    float d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

    o[0] = d * o[0];
    o[1] = d * o[1];
    o[2] = d * o[2];
    o[3] = d * o[3];
    o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
    o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
    o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
    o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));
    o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
    o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
    o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
    o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));
    o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
    o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
    o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
    o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

    return result;
}

mat4_t mat4_translation(vec3_t position) {
	mat4_t result = mat4_identity();
    result.Elements[12] = position.x;
    result.Elements[13] = position.y;
    result.Elements[14] = position.z;
    return result;
}

mat4_t mat4_scale(vec3_t scale) {
	mat4_t result = mat4_identity();
    result.Elements[0] = scale.x;
    result.Elements[5] = scale.y;
    result.Elements[10] = scale.z;
    return result;
}

mat4_t mat4_transpose(mat4_t matrix) {
	mat4_t out_matrix = mat4_identity();
    out_matrix.Elements[0] = matrix.Elements[0];
    out_matrix.Elements[1] = matrix.Elements[4];
    out_matrix.Elements[2] = matrix.Elements[8];
    out_matrix.Elements[3] = matrix.Elements[12];
    out_matrix.Elements[4] = matrix.Elements[1];
    out_matrix.Elements[5] = matrix.Elements[5];
    out_matrix.Elements[6] = matrix.Elements[9];
    out_matrix.Elements[7] = matrix.Elements[13];
    out_matrix.Elements[8] = matrix.Elements[2];
    out_matrix.Elements[9] = matrix.Elements[6];
    out_matrix.Elements[10] = matrix.Elements[10];
    out_matrix.Elements[11] = matrix.Elements[14];
    out_matrix.Elements[12] = matrix.Elements[3];
    out_matrix.Elements[13] = matrix.Elements[7];
    out_matrix.Elements[14] = matrix.Elements[11];
    out_matrix.Elements[15] = matrix.Elements[15];
    return out_matrix;
}

mat4_t mat4_euler_x(float angle_radians) {
    mat4_t out_matrix = mat4_identity();
    float c = cos(angle_radians);
    float s = sin(angle_radians);
    out_matrix.Elements[5] = c;
    out_matrix.Elements[6] = s;
    out_matrix.Elements[9] = -s;
    out_matrix.Elements[10] = c;
    return out_matrix;
}

mat4_t mat4_euler_y(float angle_radians) {
    mat4_t out_matrix = mat4_identity();
    float c = cos(angle_radians);
    float s = sin(angle_radians);

    out_matrix.Elements[0] = c;
    out_matrix.Elements[2] = -s;
    out_matrix.Elements[8] = s;
    out_matrix.Elements[10] = c;
    return out_matrix;
}

mat4_t mat4_euler_z(float angle_radians) {
    mat4_t out_matrix = mat4_identity();

    float c = cos(angle_radians);
    float s = sin(angle_radians);

    out_matrix.Elements[0] = c;
    out_matrix.Elements[1] = s;
    out_matrix.Elements[4] = -s;
    out_matrix.Elements[5] = c;
    return out_matrix;
}

mat4_t mat4_euler_xyz(float x_radians, float y_radians, float z_radians) {
    mat4_t rx = mat4_euler_x(x_radians);
    mat4_t ry = mat4_euler_y(y_radians);
    mat4_t rz = mat4_euler_z(z_radians);
    mat4_t out_matrix = mat4_dot(rx, ry);
    out_matrix = mat4_dot(out_matrix, rz);
    return out_matrix;

}


#endif // CGMATH_IMPLEMENTATION


#endif // __CGMATH_H__
