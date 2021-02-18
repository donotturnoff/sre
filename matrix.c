#include "matrix.h"
#include <string.h>

Matrix4x4 mult_m4x4_m4x4(Matrix4x4 m1, Matrix4x4 m2) {
	Matrix4x4 r = {.arr = {
		{
			m1.arr[0][0]*m2.arr[0][0]+m1.arr[0][1]*m2.arr[1][0]+m1.arr[0][2]*m2.arr[2][0]+m1.arr[0][3]*m2.arr[3][0],
			m1.arr[0][0]*m2.arr[0][1]+m1.arr[0][1]*m2.arr[1][1]+m1.arr[0][2]*m2.arr[2][1]+m1.arr[0][3]*m2.arr[3][1],
			m1.arr[0][0]*m2.arr[0][2]+m1.arr[0][1]*m2.arr[1][2]+m1.arr[0][2]*m2.arr[2][2]+m1.arr[0][3]*m2.arr[3][2],
			m1.arr[0][0]*m2.arr[0][3]+m1.arr[0][1]*m2.arr[1][3]+m1.arr[0][2]*m2.arr[2][3]+m1.arr[0][3]*m2.arr[3][3]
		},
		{
			m1.arr[1][0]*m2.arr[0][0]+m1.arr[1][1]*m2.arr[1][0]+m1.arr[1][2]*m2.arr[2][0]+m1.arr[1][3]*m2.arr[3][0],
			m1.arr[1][0]*m2.arr[0][1]+m1.arr[1][1]*m2.arr[1][1]+m1.arr[1][2]*m2.arr[2][1]+m1.arr[1][3]*m2.arr[3][1],
			m1.arr[1][0]*m2.arr[0][2]+m1.arr[1][1]*m2.arr[1][2]+m1.arr[1][2]*m2.arr[2][2]+m1.arr[1][3]*m2.arr[3][2],
			m1.arr[1][0]*m2.arr[0][3]+m1.arr[1][1]*m2.arr[1][3]+m1.arr[1][2]*m2.arr[2][3]+m1.arr[1][3]*m2.arr[3][3]
		},
		{
			m1.arr[2][0]*m2.arr[0][0]+m1.arr[2][1]*m2.arr[1][0]+m1.arr[2][2]*m2.arr[2][0]+m1.arr[2][3]*m2.arr[3][0],
			m1.arr[2][0]*m2.arr[0][1]+m1.arr[2][1]*m2.arr[1][1]+m1.arr[2][2]*m2.arr[2][1]+m1.arr[2][3]*m2.arr[3][1],
			m1.arr[2][0]*m2.arr[0][2]+m1.arr[2][1]*m2.arr[1][2]+m1.arr[2][2]*m2.arr[2][2]+m1.arr[2][3]*m2.arr[3][2],
			m1.arr[2][0]*m2.arr[0][3]+m1.arr[2][1]*m2.arr[1][3]+m1.arr[2][2]*m2.arr[2][3]+m1.arr[2][3]*m2.arr[3][3]
		},
		{
			m1.arr[3][0]*m2.arr[0][0]+m1.arr[3][1]*m2.arr[1][0]+m1.arr[3][2]*m2.arr[2][0]+m1.arr[3][3]*m2.arr[3][0],
			m1.arr[3][0]*m2.arr[0][1]+m1.arr[3][1]*m2.arr[1][1]+m1.arr[3][2]*m2.arr[2][1]+m1.arr[3][3]*m2.arr[3][1],
			m1.arr[3][0]*m2.arr[0][2]+m1.arr[3][1]*m2.arr[1][2]+m1.arr[3][2]*m2.arr[2][2]+m1.arr[3][3]*m2.arr[3][2],
			m1.arr[3][0]*m2.arr[0][3]+m1.arr[3][1]*m2.arr[1][3]+m1.arr[3][2]*m2.arr[2][3]+m1.arr[3][3]*m2.arr[3][3]
		}
	}};
	return r;
}

Matrix4x3 mult_m4x4_m4x3(Matrix4x4 m1, Matrix4x3 m2) {
	Matrix4x3 r = {.arr = {
		{
			m1.arr[0][0]*m2.arr[0][0]+m1.arr[0][1]*m2.arr[1][0]+m1.arr[0][2]*m2.arr[2][0]+m1.arr[0][3]*m2.arr[3][0],
			m1.arr[0][0]*m2.arr[0][1]+m1.arr[0][1]*m2.arr[1][1]+m1.arr[0][2]*m2.arr[2][1]+m1.arr[0][3]*m2.arr[3][1],
			m1.arr[0][0]*m2.arr[0][2]+m1.arr[0][1]*m2.arr[1][2]+m1.arr[0][2]*m2.arr[2][2]+m1.arr[0][3]*m2.arr[3][2]
		},
		{
			m1.arr[1][0]*m2.arr[0][0]+m1.arr[1][1]*m2.arr[1][0]+m1.arr[1][2]*m2.arr[2][0]+m1.arr[1][3]*m2.arr[3][0],
			m1.arr[1][0]*m2.arr[0][1]+m1.arr[1][1]*m2.arr[1][1]+m1.arr[1][2]*m2.arr[2][1]+m1.arr[1][3]*m2.arr[3][1],
			m1.arr[1][0]*m2.arr[0][2]+m1.arr[1][1]*m2.arr[1][2]+m1.arr[1][2]*m2.arr[2][2]+m1.arr[1][3]*m2.arr[3][2]
		},
		{
			m1.arr[2][0]*m2.arr[0][0]+m1.arr[2][1]*m2.arr[1][0]+m1.arr[2][2]*m2.arr[2][0]+m1.arr[2][3]*m2.arr[3][0],
			m1.arr[2][0]*m2.arr[0][1]+m1.arr[2][1]*m2.arr[1][1]+m1.arr[2][2]*m2.arr[2][1]+m1.arr[2][3]*m2.arr[3][1],
			m1.arr[2][0]*m2.arr[0][2]+m1.arr[2][1]*m2.arr[1][2]+m1.arr[2][2]*m2.arr[2][2]+m1.arr[2][3]*m2.arr[3][2]
		},
		{
			m1.arr[3][0]*m2.arr[0][0]+m1.arr[3][1]*m2.arr[1][0]+m1.arr[3][2]*m2.arr[2][0]+m1.arr[3][3]*m2.arr[3][0],
			m1.arr[3][0]*m2.arr[0][1]+m1.arr[3][1]*m2.arr[1][1]+m1.arr[3][2]*m2.arr[2][1]+m1.arr[3][3]*m2.arr[3][1],
			m1.arr[3][0]*m2.arr[0][2]+m1.arr[3][1]*m2.arr[1][2]+m1.arr[3][2]*m2.arr[2][2]+m1.arr[3][3]*m2.arr[3][2]
		}
	}};
	return r;
}

Vector4 mult_m4x4_v4(Matrix4x4 m, Vector4 v) {
	Vector4 r = {.arr = {
		m.arr[0][0]*v.arr[0]+m.arr[0][1]*v.arr[1]+m.arr[0][2]*v.arr[2]+m.arr[0][3]*v.arr[3],
		m.arr[1][0]*v.arr[0]+m.arr[1][1]*v.arr[1]+m.arr[1][2]*v.arr[2]+m.arr[1][3]*v.arr[3],
		m.arr[2][0]*v.arr[0]+m.arr[2][1]*v.arr[1]+m.arr[2][2]*v.arr[2]+m.arr[2][3]*v.arr[3],
		m.arr[3][0]*v.arr[0]+m.arr[3][1]*v.arr[1]+m.arr[3][2]*v.arr[2]+m.arr[3][3]*v.arr[3]
	}};
	return r;
}

Vector3 cross(Vector3 v1, Vector3 v2) {
	Vector3 r = {.arr = {v1.arr[1]*v2.arr[2]-v1.arr[2]*v2.arr[1], v1.arr[2]*v2.arr[0]-v1.arr[0]*v2.arr[2], v1.arr[0]*v2.arr[1]-v1.arr[1]*v2.arr[0]}};
	return r;
}

double dot_v3(Vector3 v1, Vector3 v2) {
	double r = v1.arr[0]*v2.arr[0]+v1.arr[1]*v2.arr[1]+v1.arr[2]*v2.arr[2];
	return r;
}

Vector3 add_v3(Vector3 v1, Vector3 v2) {
	Vector3 r = {.arr = {v1.arr[0]+v2.arr[0], v1.arr[1]+v2.arr[1], v1.arr[2]+v2.arr[2]}};
	return r;
}

Vector3 subtract_v3(Vector3 v1, Vector3 v2) {
	Vector3 r = {.arr = {v1.arr[0]-v2.arr[0], v1.arr[1]-v2.arr[1], v1.arr[2]-v2.arr[2]}};
	return r;
}

Vector3 normalise_v3(Vector3 v) {
	double denom = sqrt(v.arr[0]*v.arr[0]+v.arr[1]*v.arr[1]+v.arr[2]*v.arr[2]);
    if (denom == 0) {
        Vector3 r = {.arr = {0, 0, 0}};
        return r;
    } else {
        Vector3 r = {.arr = {v.arr[0]/denom, v.arr[1]/denom, v.arr[2]/denom}};
        return r;
    }
}

Vector3 negate_v3(Vector3 v) {
	Vector3 r = {.arr = {-v.arr[0], -v.arr[1], -v.arr[2]}};
    return r;
}

Vector4 extend_v3(Vector3 v, double x) {
	Vector4 r;
	for (int i = 0; i < 3; i++) {
		r.arr[i] = v.arr[i];
	}
	r.arr[3] = x;
	return r;
}

Vector4 homogenise_v3(Vector3 v) {
	return extend_v3(v, 1);
}

Matrix4x3 homogenise_m3x3(Matrix3x3 m) {
	Matrix4x3 r;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			r.arr[j][i] = m.arr[j][i];
		}
		r.arr[3][i] = 1;
	}
	return r;
}

Vector3 dehomogenise_v4(Vector4 v) {
	double w = v.arr[3];
	Vector3 r;
	for (int i = 0; i < 3; i++) {
		r.arr[i] = v.arr[i]/w;
	}
	return r;
}

Matrix3x3 dehomogenise_m4x3(Matrix4x3 m) {
	Matrix3x3 r;
	for (int j = 0; j < 3; j++) {
		double w = m.arr[3][j];
		for (int i = 0; i < 3; i++) {
			r.arr[i][j] = m.arr[i][j]/w;
		}
	}
	return r;
}

Matrix3x3 v3s_to_m3x3(Vector3 va, Vector3 vb, Vector3 vc) {
	Matrix3x3 r;
	for (int i = 0; i < 3; i++) {
		r.arr[i][0] = va.arr[i];
	}
	for (int i = 0; i < 3; i++) {
		r.arr[i][1] = vb.arr[i];
	}
	for (int i = 0; i < 3; i++) {
		r.arr[i][2] = vc.arr[i];
	}
	return r;
}

Matrix4x4 v4s_to_m4x4(Vector4 va, Vector4 vb, Vector4 vc, Vector4 vd) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++) {
		r.arr[i][0] = va.arr[i];
	}
	for (int i = 0; i < 4; i++) {
		r.arr[i][1] = vb.arr[i];
	}
	for (int i = 0; i < 4; i++) {
		r.arr[i][2] = vc.arr[i];
	}
	for (int i = 0; i < 4; i++) {
		r.arr[i][3] = vd.arr[i];
	}
	return r;
}

void print_array(size_t height, double arr[height]) {
	for (int i = 0; i < height; i++) {
		printf("%f ", arr[i]);
	}
	printf("\n");
}

void print_2d_array(size_t width, size_t height, double arr[height][width]) {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			printf("%f ", arr[j][i]);
		}
		printf("\n");
	}
}
