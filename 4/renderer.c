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
#include <stdio.h>
#include <SDL2/SDL.h>

#include "renderer.h"
#include "cache.h"

struct renderer {
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
};

renderer *renderer_new() {
	renderer *new_renderer;
	new_renderer = malloc(sizeof(renderer));

	SDL_Init(SDL_INIT_VIDEO);
	// No fancy scaleing for this tutorial
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &new_renderer->sdl_window, &new_renderer->sdl_renderer);
	// SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	// SDL_RenderSetLogicalSize(new_renderer->sdl_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return new_renderer;
}

void renderer_free(renderer *renderer) {
	SDL_DestroyRenderer(renderer->sdl_renderer);
	SDL_DestroyWindow(renderer->sdl_window);
	SDL_Quit();

	free(renderer);
}

void renderer_render(renderer *renderer, world *world, cache *cache) {
	// Clear surface
	SDL_RenderClear(renderer->sdl_renderer);

	// RenderCopy legit surfaces
	for(int i = 0; i < MAX_ENTITY; i++) {
		int mask = world->mask[i];
		if ((mask & GRAPHIC) == GRAPHIC) {
			(void)printf("Rendering entity %d with image %s\n", i, world->graphics[i].image_file);
			// Get image size and position info, if present.  Else,
			// image fills up entire screen.
			if(((mask & POSITION) == POSITION) && ((mask & SIZE) == SIZE)) {
				SDL_Rect rect;
				rect.x = world->positions[i].x;
				rect.y = world->positions[i].y;
				rect.w = world->sizes[i].x;
				rect.h = world->sizes[i].y;
				SDL_RenderCopy(renderer->sdl_renderer, cache_get(&cache, renderer->sdl_renderer, world->graphics[i].image_file), NULL, &rect);
			} else {
				SDL_RenderCopy(renderer->sdl_renderer, cache_get(&cache, renderer->sdl_renderer, world->graphics[i].image_file), NULL, NULL);
			}
		}
	}

	// Update screen surface
	SDL_RenderPresent(renderer->sdl_renderer);
}

