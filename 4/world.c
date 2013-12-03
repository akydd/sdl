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
	for(int i = 0; i < MAX_ENTITY; i++) {
		world_delete_entity(world, i);
	}
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
	if((world->mask[entity_id] | POSITION) == POSITION) {
		world->mask[entity_id] &= ~(POSITION);
	}
}

void world_add_size_component(world *world, int entity_id, int x, int y) {
	world->mask[entity_id] |= SIZE;
	world->sizes[entity_id].x = x;
	world->sizes[entity_id].y = y;
}

void world_remove_size_component(world *world, int entity_id) {
	if((world->mask[entity_id] | SIZE) == SIZE) {
		world->mask[entity_id] &= ~(SIZE);
	}
}

void world_delete_entity(world *world, int entity_id) {
	// No need to remove position and size components, as they aren't
	// malloced.
	world_remove_graphic_component(world, entity_id);
	world->mask[entity_id] = NONE;
}
