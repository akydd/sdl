/*
 * =================================================================
 *
 *       Filename:  world.c
 *
 *    Description:  Holds and manages the game entities and their components
 *
 *        Version:  1.0
 *        Created:  11/11/2013 04:32:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "world.h"

world *world_new(void) {
	world *new_world;
	new_world = malloc(sizeof(world));

	for(int i = 0; i < MAX_ENTITY; i++) {
		// initialize all masks to NONE
		new_world->mask[i] = NONE;
		// set all graphic data to NULL
		new_world->graphics[i].image_file = NULL;
	}

	return new_world;
}

void world_free(world *world) {
	world_delete_all_entities(world);
	free(world);
	world = NULL;
}

int world_create_entity(world *world) {
	for(int id = 0; id < MAX_ENTITY; id++) {
		if (world->mask[id] == NONE) {
			return id;
		}
	}
	return -1;
}

void world_add_graphic_component(world *world, int entity_id, char *imagefile) {
	// Allocate memory for imagefile string & copy into graphic struct
	world->graphics[entity_id].image_file = malloc(strlen(imagefile) + 1);
	(void)strcpy(world->graphics[entity_id].image_file, imagefile);
	// set new mask
	world->mask[entity_id] |= GRAPHIC;
}

void world_remove_graphic_component(world *world, int entity_id) {
	// we check that the bit is set here so that we know when to call free
	if((world->mask[entity_id] | GRAPHIC) == GRAPHIC) {
		// free graphic component data, if any, and unmask
		if (world->graphics[entity_id].image_file != NULL) {
			free(world->graphics[entity_id].image_file);
			world->graphics[entity_id].image_file = NULL;
		}
		world->mask[entity_id] &= ~(GRAPHIC);
	}
}

void world_add_position_component(world *world, int entity_id, int x, int y) {
	world->mask[entity_id] |= POSITION;
	world->positions[entity_id].x = x;
	world->positions[entity_id].y = y;
}

void world_remove_position_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(POSITION);
}

void world_add_size_component(world *world, int entity_id, int x, int y) {
	world->mask[entity_id] |= SIZE;
	world->sizes[entity_id].x = x;
	world->sizes[entity_id].y = y;
}

void world_remove_size_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(SIZE);
}

void world_add_color_component(world *world, int entity_id, int r, int g, int b, int a) {
	world->mask[entity_id] |= COLOR;
	world->colors[entity_id].r = r;
	world->colors[entity_id].g = g;
	world->colors[entity_id].b = b;
	world->colors[entity_id].a = a;
}

void world_remove_color_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(COLOR);
}

void world_add_outline_color_component(world *world, int entity_id, int r, int g, int b, int a) {
	world->mask[entity_id] |= OUTLINE_COLOR;
	world->outline_colors[entity_id].r = r;
	world->outline_colors[entity_id].g = g;
	world->outline_colors[entity_id].b = b;
	world->outline_colors[entity_id].a = a;
}

void world_remove_outline_color_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(OUTLINE_COLOR);
}

void world_add_point_component(world *world, int entity_id) {
	world->mask[entity_id] |= POINT;
}

void world_remove_point_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(POINT);
}

void world_add_line_component(world *world, int entity_id, int x1, int y1, int x2, int y2) {
	world->mask[entity_id] |= LINE;
	world->lines[entity_id].x1 = x1;
	world->lines[entity_id].y1 = y1;
	world->lines[entity_id].x2 = x2;
	world->lines[entity_id].y2 = y2;
}

void world_remove_line_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(LINE);
}

void world_add_rectangle_component(world *world, int entity_id) {
	world->mask[entity_id] |= RECT;
}

void world_remove_rectangle_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(RECT);
}

void world_add_sprite_component(world *world, int entity_id, int x, int y, int w, int h) {
	world->mask[entity_id] |= SPRITE;
	world->sprites[entity_id].x = x;
	world->sprites[entity_id].y = y;
	world->sprites[entity_id].w = w;
	world->sprites[entity_id].h = h;
}

void world_remove_sprite_component(world *world, int entity_id) {
	world->mask[entity_id] &= ~(SPRITE);
}

void world_add_animated_sprite_component(world *world, int entity_id, char *imagefile, int num_frames, ...) {
	va_list sprite_list;
	va_start(sprite_list, num_frames);

	world->mask[entity_id] |= ANIMATED_SPRITE;
	// Copy imagefile string into animated_sprite struct
	world->animated_sprites[entity_id].image_file = malloc(strlen(imagefile) + 1);
	(void)strcpy(world->animated_sprites[entity_id].image_file, imagefile);

	// Copy sprites into animated_sprite struct as array of sprites
	world->animated_sprites[entity_id].sprites = malloc(num_frames * sizeof(sprite));
	for(int i = 0; i < num_frames; i++) {
		world->animated_sprites[entity_id].sprites[i] = va_arg(sprite_list, sprite);
	}
	va_end(sprite_list);
}

void world_remove_animated_sprite_component(world *world, int entity_id) {
	// we check that the bit is set here so that we know when to call free
	if((world->mask[entity_id] | ANIMATED_SPRITE) == ANIMATED_SPRITE) {
		// free image file name
		if (world->animated_sprites[entity_id].image_file != NULL) {
			free(world->animated_sprites[entity_id].image_file);
			world->animated_sprites[entity_id].image_file = NULL;
		}
		// free sprite array
		if (world->animated_sprites[entity_id].sprites != NULL) {
			free(world->animated_sprites[entity_id].sprites);
			world->animated_sprites[entity_id].sprites = NULL;
		}
		world->mask[entity_id] &= ~(ANIMATED_SPRITE);
	}
}

void world_delete_entity(world *world, int entity_id) {
	// Delete these components just in case, as they contain memory that is
	// malloced.
	world_remove_graphic_component(world, entity_id);
	world_remove_animated_sprite_component(world, entity_id);
	world->mask[entity_id] = NONE;
}

void world_delete_all_entities(world *world) {
	for(int id = 0; id < MAX_ENTITY; id++) {
		if (world->mask[id] != NONE) {
			world_delete_entity(world, id);
		}
	}
}
