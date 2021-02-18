#include "camera.h"

Matrix4x4 get_view_matrix(Camera camera) {
	Vector4 right = extend_v3(cross(camera.up, camera.forward), 0);
	Vector4 up = extend_v3(camera.up, 0);
	Vector4 forward = extend_v3(camera.forward, 0);
	Vector4 location = homogenise_v3(negate_v3(camera.location));
	Matrix4x4 r = v4s_to_m4x4(right, up, forward, location);
	return r;
}

Matrix4x4 get_projection_matrix(ViewFrustum vf) {
	double w = vf.width;
	double h = vf.height;
	double n = vf.near;
	double f = vf.far;
	
	Matrix4x4 r;
	
	if (vf.projection == ORTHOGRAPHIC) {
		r = (Matrix4x4){.arr = {
			{2/w, 0, 0, 0},
			{0, 2/h, 0, 0},
			{0, 0, -2/(f-n), -(f+n)/(f-n)},
			{0, 0, 0, 1}
		}};
	} else {
		r = (Matrix4x4){.arr = {
			{n/w, 0, 0, 0},
			{0, n/h, 0, 0},
			{0, 0, -(f+n)/(f-n), -2*f*n/(f-n)},
			{0, 0, -1, 0}
		}};
	}
	return r;
}
