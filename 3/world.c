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
		delete_entity(world, i);
	}
	free(world);
	world = NULL;
}

int create_entity(world *world) {
	for(int id = 0; id < MAX_ENTITY; id++) {
		if (world->mask[id] == NONE) {
			return id;
		}
	}
	return -1;
}

int create_entity_with_graphic(world *world, char *imagefile) {
	// create the entity
	int entity_id = create_entity(world);
	// Allocate memory for imagefile string & copy into graphic struct
	world->graphics[entity_id].image_file = malloc(strlen(imagefile) + 1);
	(void)strcpy(world->graphics[entity_id].image_file, imagefile);
	// set new mask
	world->mask[entity_id] |= GRAPHIC;
	
	return entity_id;
}

void delete_entity(world *world, int entity_id) {
	// free graphic component data, if any
	if (world->graphics[entity_id].image_file != NULL) {
		free(world->graphics[entity_id].image_file);
		world->graphics[entity_id].image_file = NULL;
	}
	world->mask[entity_id] = NONE;
}
