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
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "world.h"
#include "cache.h"
#include "renderer.h"

int main(int argc, char **argv)
{
	// setup game world
	world *game_world = world_new();
	// setup surface cache
	cache *cache = cache_new();
	// setup renderer
	renderer *renderer = renderer_new();
	// create game entity representing screen background graphic
	int entity = create_entity_with_graphic(game_world, "image.bmp");

	int quit = 0;
	SDL_Event event;
	while(!quit) {
		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}
		renderer_render(renderer, game_world, cache);
	}
		
	// tear down
	delete_entity(game_world, entity);
	renderer_free(renderer);
	cache_free(&cache);
	world_free(game_world);

	return 0;
}
