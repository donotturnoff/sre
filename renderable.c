#include "renderable.h"

Matrix4x4 get_model_matrix(Model m) {
	Vector4 right = extend_v3(cross(m.up, m.forward), 0);
	Vector4 up = extend_v3(m.up, 0);
	Vector4 forward = extend_v3(m.forward, 0);
	Vector4 origin = homogenise_v3(m.origin);
	Matrix4x4 r = v4s_to_m4x4(right, up, forward, origin);
	return r;
}
