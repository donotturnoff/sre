#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

typedef struct {
	double arr[4][4];
} Matrix4x4;

typedef struct {
	double arr[4][3];
} Matrix4x3;

typedef struct {
	double arr[3][3];
} Matrix3x3;

typedef struct {
	double arr[3];
} Vector3;

typedef struct {
	double arr[4];
} Vector4;

Matrix4x4 mult_m4x4_m4x4(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x3 mult_m4x4_m4x3(Matrix4x4 m1, Matrix4x3 m2);
Vector4 mult_m4x4_v4(Matrix4x4 m, Vector4 v);

Vector3 cross(Vector3 v1, Vector3 v2);
double dot_v3(Vector3 v1, Vector3 v2);
Vector3 add_v3(Vector3 v1, Vector3 v2);
Vector3 subtract_v3(Vector3 v1, Vector3 v2);

Vector3 normalise_v3(Vector3 v);
Vector3 negate_v3(Vector3 v);

Vector4 extend_v3(Vector3 v, double x);
Vector4 homogenise_v3(Vector3 v);
Matrix4x3 homogenise_m3x3(Matrix3x3 m);
Vector3 dehomogenise_v4(Vector4 v);
Matrix3x3 dehomogenise_m4x3(Matrix4x3 v);
Matrix3x3 v3s_to_m3x3(Vector3 va, Vector3 vb, Vector3 vc);
Matrix4x4 v4s_to_m4x4(Vector4 va, Vector4 vb, Vector4 vc, Vector4 vd);

void print_array(size_t height, double arr[height]);
void print_2d_array(size_t width, size_t height, double arr[height][width]);

#endif
