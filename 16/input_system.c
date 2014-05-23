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

int entity_is_renderable(world *world, int id) {
    if((world->mask[id] & GRAPHIC) == GRAPHIC || (world->mask[id] & TEXT) == TEXT || (world->mask[id] & ANIMATED_SPRITE) == ANIMATED_SPRITE) {
        return 1;
    }
    return 0;
}

void input_system_update(SDL_Event e, world *world) {
	if(e.type == SDL_KEYDOWN) {
		int new_entity;

		switch(e.key.keysym.sym)
		{
			case SDLK_UP:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_graphic_component(world, new_entity, "../images/sprites.png");
			world_add_sprite_component(world, new_entity, 0, 588, 100, 100);
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 0);
			break;

			case SDLK_DOWN:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_graphic_component(world, new_entity, "../images/sprites.png");
			world_add_sprite_component(world, new_entity, 0, 88, 100, 100);
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 380);
			break;

			case SDLK_LEFT:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_graphic_component(world, new_entity, "../images/sprites.png");
			world_add_sprite_component(world, new_entity, 0, 188, 100, 100);
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 0, 190);
			break;

			case SDLK_RIGHT:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_graphic_component(world, new_entity, "../images/sprites.png");
			world_add_sprite_component(world, new_entity, 0, 388, 100, 100);
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 540, 190);
			break;

			case SDLK_p:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_point_component(world, new_entity);
			world_add_position_component(world, new_entity, 100, 100);
			world_add_color_component(world, new_entity, 0xFF, 0xFF, 0x00, 0xFF);
			break;

			case SDLK_l:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_line_component(world, new_entity, 0, 240, 640, 240);
			world_add_color_component(world, new_entity, 0x00, 0x00, 0xFF, 0xFF);
			break;

			case SDLK_o:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_rectangle_component(world, new_entity);
			world_add_size_component(world, new_entity, 320, 240);
			world_add_position_component(world, new_entity, 320, 240);
			world_add_outline_color_component(world, new_entity, 0x00, 0xFF, 0x00, 0xFF);
			break;

			case SDLK_f:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_rectangle_component(world, new_entity);
			world_add_size_component(world, new_entity, 160, 120);
			world_add_position_component(world, new_entity, 240, 180);
			world_add_color_component(world, new_entity, 0xFF, 0x00, 0x00, 0xFF);
			break;

			case SDLK_r:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & COLOR) == COLOR) {
						world->colors[i].r -= 32;
					} else {
						world_add_color_component(world, i, 255 - 32, 255, 255, 255);
					}
				}
			}
			break;

			case SDLK_g:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & COLOR) == COLOR) {
						world->colors[i].g -= 32;
					} else {
						world_add_color_component(world, i, 255, 255 - 32, 255, 255);
					}
				}
			}
			break;

			case SDLK_b:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & COLOR) == COLOR) {
						world->colors[i].b -= 32;
					} else {
						world_add_color_component(world, i, 255, 255, 255 - 32, 255);
					}
				}
			}
			break;

			case SDLK_a:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & COLOR) == COLOR) {
						world->colors[i].a -= 32;
					} else {
						world_add_color_component(world, i, 255, 255, 255, 255 - 32);
					}
				}
			}
			break;

			case SDLK_t:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & ROTATION) == ROTATION) {
						world->rotations[i].angle++;
					} else {
						world_add_rotation_component(world, i, 0, 0, 0, 0);
					}
				}
			}
			break;

			case SDLK_h:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & ROTATION) == ROTATION) {
						world->rotations[i].flip = 1;
					} else {
						world_add_rotation_component(world, i, 0, 0, 0, 1);
					}
				}
			}
			break;

			case SDLK_v:
			for(int i = 0; i < MAX_ENTITY; i++) {
                if(entity_is_renderable(world, i) == 1) {
					if((world->mask[i] & ROTATION) == ROTATION) {
						world->rotations[i].flip = 2;
					} else {
						world_add_rotation_component(world, i, 0, 0, 0, 2);
					}
				}
			}
			break;

			case SDLK_s:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			sprite frame1 = {0, 0, 64, 205};
			sprite frame2 = {64, 0, 64, 205};
			sprite frame3 = {128, 0, 64, 205};
			sprite frame4 = {196, 0, 64, 205};
			world_add_animated_sprite_component(world, new_entity, "../images/foo.png", 4, frame1, frame2, frame3, frame4);
			world_add_size_component(world, new_entity, 64, 205);
			world_add_position_component(world, new_entity, 270, 196);
			break;

            case SDLK_w:
            world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_text_component(world, new_entity, "YEAH!", "/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-R.ttf", 16, 0);
			world_add_position_component(world, new_entity, 270, 196);
            break;

			default:
			world_delete_all_entities(world);
			new_entity = world_create_entity(world);
			world_add_graphic_component(world, new_entity, "../images/sprites.png");
			world_add_sprite_component(world, new_entity, 0, 0, 100, 88);
			world_add_size_component(world, new_entity, 100, 100);
			world_add_position_component(world, new_entity, 270, 196);
			break;
		}
	}
}
