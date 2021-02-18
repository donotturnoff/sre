#ifndef SRE_H
#define SRE_H

#include "camera.h"
#include "renderable.h"
#include "material.h"
#include "light.h"
#include "matrix.h"
#include <stdlib.h>
#include <math.h>

typedef struct {
	Colour ambient_light;
	Colour background_colour;
} RenderContext;

void render(Camera camera, Model **models, size_t models_len, Light *lights, size_t lights_len, RenderContext ctx, size_t width, size_t height, double *z_buf, char *col_buf, Triangle *tri_buf);

#endif
