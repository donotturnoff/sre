#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

enum Projection {
	PERSPECTIVE, ORTHOGRAPHIC
};

typedef struct {
	int projection;
	double width;
	double height;
	double near;
	double far;
} ViewFrustum;

typedef struct {
	Vector3 location;
	Vector3 up;
	Vector3 forward;
	ViewFrustum vf;
} Camera;

Matrix4x4 get_view_matrix(Camera camera);
Matrix4x4 get_projection_matrix(ViewFrustum vf);

#endif
