/*
 * =====================================================================================
 *
 *       Filename:  input_system.c
 *
 *    Description:  Implementation of the Input System
 *
 *        Version:  1.0
 *        Created:  13-12-01 08:50:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "world.h"
#include "input_system.h"

void input_system_update(SDL_Event e, world *world) {
	if(e.type == SDL_KEYDOWN) {
		world_delete_all_entities(world);
		int new_entity = world_create_entity(world);
		(void)printf("New entity %d\n", new_entity);

		switch(e.key.keysym.sym)
		{
			case SDLK_UP:
			world_add_graphic_component(world, new_entity, "up_arrow.bmp");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 0);
			break;

			case SDLK_DOWN:
			world_add_graphic_component(world, new_entity, "down_arrow.bmp");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 380);
			break;

			case SDLK_LEFT:
			world_add_graphic_component(world, new_entity, "left_arrow.bmp");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 0, 190);
			break;

			case SDLK_RIGHT:
			world_add_graphic_component(world, new_entity, "right_arrow.bmp");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 540, 190);
			break;

			default:
			world_add_graphic_component(world, new_entity, "any_key.bmp");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 196);
			break;
		}
	}
}
