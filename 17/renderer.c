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
#include <SDL2/SDL_ttf.h>

#include "renderer.h"
#include "cache.h"
#include "font_cache.h"

struct renderer {
	SDL_Window *sdl_window;
	SDL_Renderer *sdl_renderer;
};

void render_graphic(renderer *renderer, world *world, cache **cache, int id);
void render_point(renderer *renderer, world *world, int id);
void render_line(renderer *renderer, world *world, int id);
void render_rectangle(renderer *renderer, world *world, int id);
void render_animated_sprite(renderer *renderer, world *world, cache ** const cache, int id);
void render_text(renderer *renderer, world *world, font_cache ** const font_cache, int id);


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

void renderer_render(renderer *renderer, world *world, cache **const cache, font_cache **const font_cache) {
	// Clear surface to black
	SDL_SetRenderDrawColor(renderer->sdl_renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer->sdl_renderer);

	// RenderCopy legit surfaces
	for(int i = 0; i < MAX_ENTITY; i++) {
		int mask = world->mask[i];
		if ((mask & GRAPHIC) == GRAPHIC) {
			render_graphic(renderer, world, cache, i);
		} else if (((mask & POINT) == POINT) && ((mask & COLOR) == COLOR) && ((mask & POSITION) == POSITION)) {
			render_point(renderer, world, i);
		} else if (((mask & LINE) == LINE) && ((mask & COLOR) == COLOR)) {
			render_line(renderer, world, i);
		} else if (((mask & RECT) == RECT) && ((mask & POSITION) == POSITION)) {
			render_rectangle(renderer, world, i);
		} else if ((mask & ANIMATED_SPRITE) == ANIMATED_SPRITE) {
			render_animated_sprite(renderer, world, cache, i);
		} else if ((mask & TEXT) == TEXT) {
			render_text(renderer, world, font_cache, i);
		}
	}

	// Update screen surface
	SDL_RenderPresent(renderer->sdl_renderer);
}

inline void render_texture(renderer *renderer, world *world, int id, int mask, SDL_Texture *texture, SDL_Rect *source_ptr, SDL_Rect *size_ptr) {
	// apply rotation
	if((mask & ROTATION) == ROTATION) {
		SDL_Point center = {world->rotations[id].x, world->rotations[id].y};
		SDL_RenderCopyEx(renderer->sdl_renderer, texture, source_ptr, size_ptr, world->rotations[id].angle, &center, world->rotations[id].flip);
	} else {
		SDL_RenderCopy(renderer->sdl_renderer, texture, source_ptr, size_ptr);
	}
}

void render_graphic(renderer *renderer, world *world, cache ** const cache, int id) {
	(void)printf("Rendering graphic %d with image %s\n", id, world->graphics[id].image_file);
	int mask = world->mask[id];
	SDL_Texture *texture = cache_get(cache, renderer->sdl_renderer, world->graphics[id].image_file);
	SDL_Rect *size_ptr = NULL;
	SDL_Rect size;
	SDL_Rect *source_ptr = NULL;
	SDL_Rect source;
	// Get image size and position info, if present.
	if(((mask & POSITION) == POSITION) && ((mask & SIZE) == SIZE)) {
		size.x = world->positions[id].x;
		size.y = world->positions[id].y;
		size.w = world->sizes[id].x;
		size.h = world->sizes[id].y;
		size_ptr = &size;
	}
	// Get sprite info, if present
	if((mask & SPRITE) == SPRITE) {
		source.x = world->sprites[id].x;
		source.y = world->sprites[id].y;
		source.w = world->sprites[id].w;
		source.h = world->sprites[id].h;
		source_ptr = &source;
	}
	// Apply color and alpha mods, if present
	if((mask & COLOR) == COLOR) {
		SDL_SetTextureColorMod(texture, world->colors[id].r, world->colors[id].g, world->colors[id].b);
		// set alpha if less than 255
		if (world->colors[id].a != 255) {
			SDL_SetTextureAlphaMod(texture, world->colors[id].a);
		}
	}

    render_texture(renderer, world, id, mask, texture, source_ptr, size_ptr);
}

void render_animated_sprite(renderer *renderer, world *world, cache ** const cache, int id) {
	(void)printf("Rendering animated sprite %d with image %s\n", id, world->animated_sprites[id].image_file);
	int mask = world->mask[id];
	SDL_Texture *texture = cache_get(cache, renderer->sdl_renderer, world->animated_sprites[id].image_file);
	SDL_Rect *size_ptr = NULL;
	SDL_Rect size;
	SDL_Rect *source_ptr = NULL;
	SDL_Rect source;

	// Get image size and position info, if present.
	if(((mask & POSITION) == POSITION) && ((mask & SIZE) == SIZE)) {
		size.x = world->positions[id].x;
		size.y = world->positions[id].y;
		size.w = world->sizes[id].x;
		size.h = world->sizes[id].y;
		size_ptr = &size;
	}

	// Get current frame
	int current_frame = world->animated_sprites[id].current_frame;
	source.x = world->animated_sprites[id].sprites[current_frame].x;
	source.y = world->animated_sprites[id].sprites[current_frame].y;
	source.w = world->animated_sprites[id].sprites[current_frame].w;
	source.h = world->animated_sprites[id].sprites[current_frame].h;
	source_ptr = &source;

	// set next frame
	int max_frame = world->animated_sprites[id].num_frames;
	current_frame++;
	if (current_frame >= max_frame) {
		current_frame -= max_frame;
	}
	world->animated_sprites[id].current_frame = current_frame;

	// Apply color and alpha mods, if present
	if((mask & COLOR) == COLOR) {
		SDL_SetTextureColorMod(texture, world->colors[id].r, world->colors[id].g, world->colors[id].b);
		// set alpha if less than 255
		if (world->colors[id].a != 255) {
			SDL_SetTextureAlphaMod(texture, world->colors[id].a);
		}
	}

    render_texture(renderer, world, id, mask, texture, source_ptr, size_ptr);

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

void render_rectangle(renderer *renderer, world *world, int id) {
	int mask = world->mask[id];
	size size = world->sizes[id];
	position pos = world->positions[id];
	SDL_Rect rect = {pos.x - size.x/2, pos.y - size.y/2, size.x, size.y};

	// Need to handle cases when rectangle has fill and outline
	if ((mask & COLOR) == COLOR) {
		(void)printf("Rendering filled rect %d\n", id);
		color color = world->colors[id];
		SDL_SetRenderDrawColor(renderer->sdl_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer->sdl_renderer, &rect);
	}
	if ((mask & OUTLINE_COLOR) == OUTLINE_COLOR) {
		(void)printf("Rendering outline rect %d\n", id);
		color color = world->outline_colors[id];
		SDL_SetRenderDrawColor(renderer->sdl_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(renderer->sdl_renderer, &rect);
	}
}

void render_text(renderer *renderer, world *world, font_cache ** const font_cache, int id) {
	(void)printf("Rendering text %d with text %s\n", id, world->texts[id].text);
    int mask = world->mask[id];
	position pos = world->positions[id];
	SDL_Rect *size_ptr = NULL;
	SDL_Rect size;

    text txt = world->texts[id];
    TTF_Font *font = font_cache_get(font_cache, txt.font, txt.size);

    // default text color is white
    SDL_Color sdl_color = {255, 255, 255, 255};
    if ((mask & COLOR) == COLOR) {
        color color = world->colors[id];
        sdl_color.r = color.r;
        sdl_color.g = color.g;
        sdl_color.b = color.b;
        sdl_color.a = color.a;
    }
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, txt.text, sdl_color);

    // text can be scaled
	if((mask & SIZE) == SIZE) {
		size.w = world->sizes[id].x;
		size.h = world->sizes[id].y;
	} else { // otherwise use default size
        size.w = text_surface->w;
        size.h = text_surface->h;
    }
    size.x = pos.x;
    size.y = pos.y;
    size_ptr = &size;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer->sdl_renderer, text_surface);
    SDL_FreeSurface(text_surface);

    render_texture(renderer, world, id, mask, texture, NULL, size_ptr);

    SDL_DestroyTexture(texture);
}
