#include "matrix.h"
#include "sre.h"
#include "material.h"
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define NORM   "\x1B[0m"

#define FBLK   "\x1B[30m"
#define FRED   "\x1B[31m"
#define FGRN   "\x1B[32m"
#define FYEL   "\x1B[33m"
#define FBLU   "\x1B[34m"
#define FMAG   "\x1B[35m"
#define FCYN   "\x1B[36m"
#define FWHT   "\x1B[37m"

#define BBLK   "\x1B[40m"
#define BRED   "\x1B[41m"
#define BGRN   "\x1B[42m"
#define BYEL   "\x1B[43m"
#define BBLU   "\x1B[44m"
#define BMAG   "\x1B[45m"
#define BCYN   "\x1B[46m"
#define BWHT   "\x1B[47m"

void draw_ascii(size_t width, size_t height, char *col_buf) {
	int length = 0;
	char buf[width*height*25];
	for (int y = height-1; y >= 0; y--) {
		for (int x = 0; x < width; x+=3) {
			int index = y*width+x;
			unsigned char r = col_buf[index];
			unsigned char g = col_buf[index+1];
			unsigned char b = col_buf[index+2];
			length += sprintf(buf+length, "\x1B[48;2;%u;%u;%um %s", r, g, b, NORM);
		}
		length += sprintf(buf+length, "\n");
	}
	printf("%s", buf);
}

void handle_keydown(SDL_KeyboardEvent *key, Camera *camera) {
    SDL_Keycode k = key->keysym.sym;
    Vector3 v = {.arr = {0, 0, 0}};
    switch (k) {
        case SDLK_w: v.arr[2] = -0.1; break;
        case SDLK_a: v.arr[0] = -0.1; break;
        case SDLK_s: v.arr[2] = 0.1; break;
        case SDLK_d: v.arr[0] = 0.1; break;
        case SDLK_SPACE: v.arr[1] = 0.1; break;
        case SDLK_LSHIFT: case SDLK_RSHIFT: v.arr[1] = -0.1; break;
        default: break;
    }
    camera->location = add_v3(camera->location, v);
}

int main(void) {	
	size_t width = 1000;
	size_t height = 1000;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        printf("Error initializing SDL: %s\n", SDL_GetError()); 
    } 
    SDL_Window* win = SDL_CreateWindow("3D",
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       SDL_WINDOWPOS_UNDEFINED, 
                                       width, height, 0);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    
	int quit = 0;
	SDL_Event e;
	
	Camera camera;
	camera.location = (Vector3){.arr = {0, 0, 0}};
	camera.up = (Vector3){.arr = {0, 1, 0}};
	camera.forward = (Vector3){.arr = {0, 0, 1}};
	camera.vf = (ViewFrustum){.projection = PERSPECTIVE, .near = 1, .far = 20, .width = 1, .height = 1};
	
	Colour white = {.r = 1, .g = 1, .b = 1};
	Colour red = {.r = 1, .g = 0, .b = 0};
	Colour green = {.r = 0, .g = 1, .b = 0};
	Colour blue = {.r = 0, .g = 0, .b = 1};
	Colour black = {.r = 0, .g = 0, .b = 0};
	
	Material red_mat = {.ambient_colour = red, .diffuse_colour = red, .shading = LINEAR_INTERPOLATION};
	Material green_mat = {.ambient_colour = green, .diffuse_colour = green, .shading = LINEAR_INTERPOLATION};
	Material blue_mat = {.ambient_colour = blue, .diffuse_colour = blue, .shading = LINEAR_INTERPOLATION};
	
	Triangle t1;
	t1.vertices[0] = (Vector3){.arr = {0, 1, 0}};
    t1.vertices[1] = (Vector3){.arr = {1, 0, 1}};
	t1.vertices[2] = (Vector3){.arr = {0, 1, 1}};
	t1.material = red_mat;
	
	Triangle t2;
	t2.vertices[0] = (Vector3){.arr = {0, 0, 1.5}};
	t2.vertices[2] = (Vector3){.arr = {0, 1, 1.5}};
	t2.vertices[1] = (Vector3){.arr = {1, 0, 1.5}};
	t2.material = green_mat;
	
	Triangle s1a;
	s1a.vertices[0] = (Vector3){.arr = {0, 0, 0}};
	s1a.vertices[1] = (Vector3){.arr = {0, 1, 0}};
	s1a.vertices[2] = (Vector3){.arr = {-1, 0, 0}};
	s1a.material = blue_mat;
	
	Triangle s1b;
	s1b.vertices[0] = (Vector3){.arr = {-1, 1, 0}};
	s1b.vertices[2] = (Vector3){.arr = {0, 1, 0}};
	s1b.vertices[1] = (Vector3){.arr = {-1, 0, 0}};
	s1b.material = blue_mat;
	
	int mn = 1;
    
	Model *model;
	int tn = 1;
	model = (Model *) malloc(3*sizeof(Vector3)+sizeof(int)+tn*sizeof(Triangle));
	model->origin = (Vector3){.arr = {0, 0, -4}};
	model->up = (Vector3){.arr = {0, 1, 0}};
	model->forward = (Vector3){.arr = {0, 0, 1}};
	model->triangles_len = tn;
	model->triangles[0] = t1;
	/*model->triangles[1] = t2;
	model->triangles[2] = s1a;
	model->triangles[3] = s1b;*/
        
    Model *models[mn];
    models[0] = model;
		
	Light lights[1];
	lights[0].location = (Vector3){{0, 0.5, -3.5}};
	lights[0].colour = white;
	lights[0].brightness = 1;
	
	RenderContext ctx = {.background_colour = white, .ambient_light = black};
	
	SDL_Surface *surface;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    SDL_Texture *texture = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	
	double *z_buf;
	char *col_buf;
	Triangle *tri_buf;
	
	while (!quit) {
		time_t start = clock();
        
		if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: quit = 1; break;
                case SDL_KEYDOWN: handle_keydown(&e.key, &camera); break;
                default: break;
            }
		}
        
		z_buf = (double *) calloc(width*height, sizeof(double));
		col_buf = (char *) calloc(width*height, sizeof(char)*4);
		tri_buf = (Triangle *) calloc(width*height, sizeof(Triangle));
			
		render(camera, models, mn, lights, 1, ctx, width, height, z_buf, col_buf, tri_buf);
        SDL_UpdateTexture(texture, NULL, (void *) col_buf, width*4);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, texture, NULL, &rect);
        SDL_RenderPresent(rend);
		
		free(z_buf);
		free(col_buf);
		free(tri_buf);
		
		time_t end = clock();
		double time = ((double) (end-start))/CLOCKS_PER_SEC;
		//printf("Render: %f\n", time);
        //SDL_Delay(1000 / 60); 
	}
	SDL_DestroyTexture(texture);
    for (int i = 0; i < mn; i++) {
        free(models[i]);
    }
	return 0;
}
