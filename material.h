#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct {
	double r;
	double g;
	double b;
} Colour;

typedef struct {

} Texture;

enum Shading {
	FLAT, LINEAR_INTERPOLATION, PHONG
};

typedef struct {
	Colour ambient_colour;
	Texture ambient_texture;
	Colour diffuse_colour;
	Texture diffuse_texture;
	Colour specular_colour;
	Texture specular_texture;
	int shading;
} Material;

#endif
