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
#include "world.h"
#include "renderer.h"

int main(int argc, char **argv)
{
	world *game_world = world_new();
	renderer *renderer = renderer_new();

	int entity = create_entity_with_graphic(game_world, "test.bmp");
	delete_entity(game_world, entity);

	renderer_free(renderer);
	world_free(game_world);

	return 0;
}
