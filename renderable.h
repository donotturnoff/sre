#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "matrix.h"
#include "material.h"

typedef struct {
	Vector3 vertices[3];
	Material material;
	int backface_cull;
	int interactive;
} Triangle;

typedef struct {
	Vector3 origin;
	Vector3 up;
	Vector3 forward;
	int triangles_len;
	Triangle triangles[];
} Model;

Matrix4x4 get_model_matrix(Model m);

#endif
