/*
 * ====================================================================
 *
 *       Filename:  renderer.c
 *
 *    Description:  SDL implementation of the render system
 *
 *        Version:  1.0
 *        Created:  11/11/2013 06:59:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * ====================================================================
 */
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "renderer.h"
#include "world.h"

struct renderer {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Surface *images[MAX_ENTITY];
};

renderer *renderer_new() {
	renderer *new_renderer;
	new_renderer = malloc(sizeof(renderer));

	// init SDL stuff
	SDL_Init(SDL_INIT_VIDEO);
	new_renderer->window = SDL_CreateWindow("SDL Rendered", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	new_renderer->surface = SDL_GetWindowSurface(new_renderer->window);

	// Init all entity SDL_Surface pointers to NULL
	for(int i = 0; i < MAX_ENTITY; i++) {
		new_renderer->images[i] = NULL;
	}
	
	return new_renderer;
}

void renderer_free(renderer *renderer) {
	// tear down SDL
	for(int i = 0; i < MAX_ENTITY; i++) {
		if (renderer->images[i] != NULL) {
			SDL_FreeSurface(renderer->images[i]);
		}
	}
	SDL_FreeSurface(renderer->surface);
	SDL_DestroyWindow(renderer->window);
	SDL_Quit();

	free(renderer);
}

void renderer_render(renderer *renderer, world *world) {
	// blit graphic componenets to the screen
	for(int i = 0; i < MAX_ENTITY; i++) {
		if ((world->mask[i] & GRAPHIC) == GRAPHIC) {
			SDL_BlitSurface(renderer->images[i], NULL, renderer->surface, NULL);
		}
	}

	// Update screen surface
	SDL_UpdateWindowSurface(renderer->window);
}

