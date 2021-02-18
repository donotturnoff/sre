#ifndef LIGHT_H
#define LIGHT_H

#include "matrix.h"
#include "material.h"

typedef struct {
	Vector3 location;
	Colour colour;
	double brightness;
} Light;

#endif
