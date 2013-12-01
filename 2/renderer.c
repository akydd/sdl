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
#include "cache.h"

struct renderer {
	SDL_Window *window;
	SDL_Surface *surface;
};

renderer *renderer_new() {
	renderer *new_renderer;
	new_renderer = malloc(sizeof(renderer));

	// init SDL stuff
	SDL_Init(SDL_INIT_VIDEO);
	new_renderer->window = SDL_CreateWindow("SDL Rendered", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	new_renderer->surface = SDL_GetWindowSurface(new_renderer->window);

	return new_renderer;
}

void renderer_free(renderer *renderer) {
	SDL_FreeSurface(renderer->surface);
	SDL_DestroyWindow(renderer->window);
	SDL_Quit();

	free(renderer);
}

void renderer_render(renderer *renderer, world *world, cache *cache) {
	// blit graphic componenets to the screen
	for(int i = 0; i < MAX_ENTITY; i++) {
		if ((world->mask[i] & GRAPHIC) == GRAPHIC) {
			SDL_BlitSurface(cache_get(&cache, world->graphics[i].image_file), NULL, renderer->surface, NULL);
		}
	}

	// Update screen surface
	SDL_UpdateWindowSurface(renderer->window);
}

