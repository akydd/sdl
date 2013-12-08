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
			world_add_graphic_component(world, new_entity, "../images/up_arrow.png");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 0);
			break;

			case SDLK_DOWN:
			world_add_graphic_component(world, new_entity, "../images/down_arrow.png");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 380);
			break;

			case SDLK_LEFT:
			world_add_graphic_component(world, new_entity, "../images/left_arrow_alpha.png");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 0, 190);
			break;

			case SDLK_RIGHT:
			world_add_graphic_component(world, new_entity, "../images/right_arrow_alpha.png");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 540, 190);
			break;

			case SDLK_p:
			world_add_point_component(world, new_entity);
			world_add_position_component(world, new_entity, 100, 100);
			world_add_color_component(world, new_entity, 0xFF, 0xFF, 0x00, 0xFF);
			break;

			case SDLK_l:
			world_add_line_component(world, new_entity, 0, 240, 640, 240);
			world_add_color_component(world, new_entity, 0x00, 0x00, 0xFF, 0xFF);
			break;

			case SDLK_o:
			world_add_rectangle_component(world, new_entity);
			world_add_size_component(world, new_entity, 320, 240);
			world_add_position_component(world, new_entity, 320, 240);
			world_add_outline_color_component(world, new_entity, 0x00, 0xFF, 0x00, 0xFF);
			break;

			case SDLK_f:
			world_add_rectangle_component(world, new_entity);
			world_add_size_component(world, new_entity, 160, 120);
			world_add_position_component(world, new_entity, 240, 180);
			world_add_color_component(world, new_entity, 0xFF, 0x00, 0x00, 0xFF);
			break;

			default:
			world_add_graphic_component(world, new_entity, "../images/any_key.png");
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 196);
			break;
		}
	}
}
