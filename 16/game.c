/*
 * =====================================================================================
 *
 *       Filename:  game.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/21/2013 08:27:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd 
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>

#include "world.h"
#include "cache.h"
#include "font_cache.h"
#include "input_system.h"
#include "renderer.h"

int main(int argc, char **argv)
{
	// setup game world
	world *game_world = world_new();
	// setup surface cache
	cache *cache = cache_new();
	// setup font cache
	font_cache *font_cache = font_cache_new();
	// setup renderer
	renderer *renderer = renderer_new();

	// main game loop
	int quit = 0;
	SDL_Event input_event;
	while(!quit) {
		while(SDL_PollEvent(&input_event)) {
			if(input_event.type == SDL_QUIT) {
				quit = 1;
			} else {
				input_system_update(input_event, game_world);
			}
		}
		renderer_render(renderer, game_world, cache);
	}
		
	// tear down
	renderer_free(renderer);
	cache_free(&cache);
	font_cache_free(&font_cache);
	world_free(game_world);

	return 0;
}
