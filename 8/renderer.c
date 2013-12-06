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

void render_graphic(renderer *renderer, world *world, cache *cache, int id, int mask);
void render_point(renderer *renderer, world *world, int id);
void render_line(renderer *renderer, world *world, int id);

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
	// Clear surface to black
	SDL_SetRenderDrawColor(renderer->sdl_renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer->sdl_renderer);

	// RenderCopy legit surfaces
	for(int i = 0; i < MAX_ENTITY; i++) {
		int mask = world->mask[i];
		if ((mask & GRAPHIC) == GRAPHIC) {
			render_graphic(renderer, world, cache, i, mask);
		} else if (((mask & POINT) == POINT) && ((mask & COLOR) == COLOR) && ((mask & POSITION) == POSITION)) {
			render_point(renderer, world, i);
		} else if (((mask & LINE) == LINE) && ((mask & COLOR) == COLOR)) {
			render_line(renderer, world, i);
		}
	}

	// Update screen surface
	SDL_RenderPresent(renderer->sdl_renderer);
}

void render_graphic(renderer *renderer, world *world, cache *cache, int id, int mask) {
	(void)printf("Rendering graphic %d with image %s\n", id, world->graphics[id].image_file);
	// Get image size and position info, if present.  Else,
	// image fills up entire screen.
	if(((mask & POSITION) == POSITION) && ((mask & SIZE) == SIZE)) {
		SDL_Rect rect;
		rect.x = world->positions[id].x;
		rect.y = world->positions[id].y;
		rect.w = world->sizes[id].x;
		rect.h = world->sizes[id].y;
		SDL_RenderCopy(renderer->sdl_renderer, cache_get(&cache, renderer->sdl_renderer, world->graphics[id].image_file), NULL, &rect);
	} else {
		SDL_RenderCopy(renderer->sdl_renderer, cache_get(&cache, renderer->sdl_renderer, world->graphics[id].image_file), NULL, NULL);
	}
}

void render_point(renderer *renderer, world *world, int id) {
	position pos = world->positions[id];
	color color = world->colors[id];
	(void)printf("Rendering point %d at %d, %d\n", id, pos.x, pos.y);

	SDL_SetRenderDrawColor(renderer->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer->sdl_renderer, pos.x, pos.y);
}

void render_line(renderer *renderer, world *world, int id) {
	color color = world->colors[id];
	line line = world->lines[id];
	(void)printf("Rendering line %d at (%d, %d) to (%d, %d)\n", id, line.x1, line.y1, line.x2, line.y2);

	SDL_SetRenderDrawColor(renderer->sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer->sdl_renderer, line.x1, line.y1, line.x2, line.y2);
}
