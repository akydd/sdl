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
#include <time.h>
#include <unistd.h>
#include "world.h"
#include "renderer.h"

int main(int argc, char **argv)
{
	// setup game world
	world *game_world = world_new();
	// setup renderer
	renderer *renderer = renderer_new();
	// create game entity representing screen background graphic
	int entity = create_entity_with_graphic(game_world, "image.bmp");

	// main loop isn't actually a loop, and doesn't depend on SDL. But it
	// depends on unistd.h.
	renderer_render(renderer, game_world);
	(void)sleep(2);
		
	// tear down
	delete_entity(game_world, entity);
	renderer_free(renderer);
	world_free(game_world);

	return 0;
}
