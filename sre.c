#include "sre.h"
#include <stdio.h>

int cull(Matrix4x3 m) {
	for (int i = 0; i < 3; i++) {
        int lt = (m.arr[i][0] < -m.arr[3][0]) && (m.arr[i][1] < -m.arr[3][1]) && (m.arr[i][2] < -m.arr[3][2]);
        int gt = (m.arr[i][0] > m.arr[3][0]) && (m.arr[i][1] > m.arr[3][1]) && (m.arr[i][2] > m.arr[3][2]);
		if (lt || gt) {
            return 1;
        }
	}
	return 0;
}

Matrix3x3 to_screen_space(Matrix3x3 ndc, size_t width, size_t height) {
	double w_2 = width/2;
	double h_2 = height/2;
	Matrix3x3 r;
	for (int i = 0; i < 3; i++) {
		r.arr[0][i] = w_2*ndc.arr[0][i]+w_2;
		r.arr[1][i] = h_2*ndc.arr[1][i]+h_2;
		r.arr[2][i] = ndc.arr[2][i]; //TODO: scale depth
	}
	return r;
}

double * compute_barycentric_weights(double a[3][3], double x, double y, double denom) {
	static double w[3];
	w[0] = ((a[1][1]-a[1][2])*(x-a[0][2])+(a[0][2]-a[0][1])*(y-a[1][2]))/denom;
	w[1] = ((a[1][2]-a[1][0])*(x-a[0][2])+(a[0][0]-a[0][2])*(y-a[1][2]))/denom;
	w[2] = 1-w[0]-w[1];
	return w;
}

void scanline(double a[3][3], Triangle t, Colour colours[3], size_t width, size_t height, double *z_buf, char *col_buf, Triangle *tri_buf) {
	
	int shading = t.material.shading;
	
	/* Determine minimum and maximum y values of triangle's vertices */
	int min_y = (int) a[1][0];
	int max_y = (int) a[1][0];
	
	for (int i = 1; i < 3; i++) {
		double v = a[1][i];
		if (v < min_y) {
			min_y = (int) v;
		} else if (v > max_y) {
			max_y = (int) v;
		}	
	}
	
	double bary_denom = (a[1][1]-a[1][2])*(a[0][0]-a[0][2])+(a[0][2]-a[0][1])*(a[1][0]-a[1][2]);
	
	/* Iterate over each scanline */
	for (int y = min_y; y < max_y; y++) { //TODO: determine whether the upper bound should be strict or not
				
		double left, right;
		int intersection = 0;
		for (int edge = 0; edge < 3; edge++) {
			
			/* Edge endpoints */
			double x1 = a[0][edge];
			double y1 = a[1][edge];
			double x2 = a[0][(edge+1)%3];
			double y2 = a[1][(edge+1)%3];
						
			/* If the scanline intersects the edge */
			if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
				double q = (((double) y) - y1)/(y2-y1);
				double x = x1 + (x2 - x1)*q;
				intersection++;
				if (intersection == 1) {
					left = x;
				} else if (intersection == 2) {
					if (left > x) {
						right = left;
						left = x;
					} else {
						right = x;
					}
					break;
				}
			}
		}
		if (intersection == 2) {
            
            left = fmax(left, 0);
            right = fmin(right, width);
						
			for (int x = left; x < right; x++) {
				double *w = compute_barycentric_weights(a, (double) x, (double) y, bary_denom);
				
				double z = w[0]*a[2][0]+w[1]*a[2][1]+w[2]*a[2][2];
				
				Colour colour;
				if (t.material.shading == FLAT) {
					colour = colours[0];
				} else if (t.material.shading == LINEAR_INTERPOLATION) {
					//TODO: change to work with textures (i.e. interpolate brightness rather than colour)
					colour.r = fmin((w[0]*colours[0].r+w[1]*colours[1].r+w[2]*colours[2].r)*255, 255);
					colour.g = fmin((w[0]*colours[0].g+w[1]*colours[1].g+w[2]*colours[2].g)*255, 255);
					colour.b = fmin((w[0]*colours[0].b+w[1]*colours[1].b+w[2]*colours[2].b)*255, 255);
				}
				size_t index = (height-y)*width+x;
				if (z < z_buf[index] || z_buf[index] == 0) {
					z_buf[index] = z;
					col_buf[index*4] = (char) colour.b;
					col_buf[index*4+1] = (char) colour.g;
					col_buf[index*4+2] = (char) colour.r;
					tri_buf[index] = t;
				}
			}
		}
	}
}

Colour compute_vertex_colour(Colour ambient_colour, Colour diffuse_colour, Vector3 normal, Vector3 vertex, RenderContext ctx, Light *lights, int lights_len) {
	double r = ambient_colour.r*ctx.ambient_light.r, g = ambient_colour.g*ctx.ambient_light.g, b = ambient_colour.b*ctx.ambient_light.b;
	for (int i = 0; i < lights_len; i++) {
		Light l = lights[i];
		Vector3 l_vector = normalise_v3(subtract_v3(l.location, vertex));
		double dot = fabs(dot_v3(normal, l_vector));
		r += diffuse_colour.r*dot*l.colour.r*l.brightness;
		g += diffuse_colour.g*dot*l.colour.g*l.brightness;
		b += diffuse_colour.b*dot*l.colour.b*l.brightness;
	}
	Colour colour = {.r = r, .g = g, .b = b};
	return colour;
}

Colour compute_pixel_colour_phong(Colour ambient_colour, Colour diffuse_colour, Colour specular_colour, double specular_exponent, Vector3 normal, Vector3 vertex, RenderContext ctx, Light *lights, int lights_len) {
	double r = ambient_colour.r*ctx.ambient_light.r, g = ambient_colour.g*ctx.ambient_light.g, b = ambient_colour.b*ctx.ambient_light.b;
	for (int i = 0; i < lights_len; i++) {
		Light l = lights[i];
		Vector3 l_vector = normalise_v3(subtract_v3(l.location, vertex));
		double n_dot_l = fabs(dot_v3(normal, l_vector));
		r += diffuse_colour.r*n_dot_l*l.colour.r*l.brightness;
		g += diffuse_colour.g*n_dot_l*l.colour.g*l.brightness;
		b += diffuse_colour.b*n_dot_l*l.colour.b*l.brightness;
	}
	Colour colour = {.r = r, .g = g, .b = b};
	return colour;
}

Vector3 *extract_world_space_vertices(Matrix4x3 world_space) {
	static Vector3 vertices[3];
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			vertices[i].arr[j] = world_space.arr[j][i];
		}
	}
	return vertices;
}

void render(Camera camera, Model **models, size_t models_len, Light *lights, size_t lights_len, RenderContext ctx, size_t width, size_t height, double *z_buf, char *col_buf, Triangle *tri_buf) {

	for (size_t i = 0; i < width*height*4; i+=4) {
		col_buf[i] = ctx.background_colour.r*255;
		col_buf[i+1] = ctx.background_colour.g*255;
		col_buf[i+2] = ctx.background_colour.b*255;
	}
	
	Matrix4x4 view_matrix = get_view_matrix(camera);
	Matrix4x4 projection_matrix = get_projection_matrix(camera.vf);
	Matrix4x4 vp = mult_m4x4_m4x4(projection_matrix, view_matrix);
	
	for (size_t i = 0; i < models_len; i++) {
		Model *mdl = models[i];
		Matrix4x4 model_matrix = get_model_matrix(*mdl);
		Matrix4x4 mvp = mult_m4x4_m4x4(vp, model_matrix);
		
		for (size_t j = 0; j < mdl->triangles_len; j++) {
			Triangle t = mdl->triangles[j];
			Matrix4x3 vertices = homogenise_m3x3(v3s_to_m3x3(t.vertices[0], t.vertices[1], t.vertices[2]));
			
			Matrix4x3 world_space = mult_m4x4_m4x3(model_matrix, vertices);
			Vector3 *world_space_vertices = extract_world_space_vertices(world_space);
			Vector3 normal = normalise_v3(cross(subtract_v3(world_space_vertices[1], world_space_vertices[0]), subtract_v3(world_space_vertices[2], world_space_vertices[0])));
					
			Matrix4x3 clip_space = mult_m4x4_m4x3(vp, world_space);
			int culled = cull(clip_space);
			if (culled == 1) {
				continue;
			}
			Matrix3x3 ndc = dehomogenise_m4x3(clip_space);
			Matrix3x3 screen_space = to_screen_space(ndc, width, height);
			
			Colour colours[3];
			if (t.material.shading == FLAT) {
				for (int i = 0; i < 3; i++) {
					colours[i] = compute_vertex_colour(t.material.ambient_colour, t.material.diffuse_colour, normal, world_space_vertices[i], ctx, lights, lights_len);
				}
				colours[0].r = (colours[0].r+colours[1].r+colours[2].r)/3;
				colours[0].g = (colours[0].g+colours[1].g+colours[2].g)/3;
				colours[0].b = (colours[0].b+colours[1].b+colours[2].b)/3;
			} else if (t.material.shading == LINEAR_INTERPOLATION) {
				for (int i = 0; i < 3; i++) {
					colours[i] = compute_vertex_colour(t.material.ambient_colour, t.material.diffuse_colour, normal, world_space_vertices[i], ctx, lights, lights_len);
				}
			}
			scanline(screen_space.arr, t, colours, width, height, z_buf, col_buf, tri_buf);
		}
	}
}
