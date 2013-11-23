/*
 * =================================================================
 *
 *       Filename:  world.h
 *
 *    Description:  Defines World struct
 *
 *        Version:  1.0
 *        Created:  11/11/2013 12:14:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * ===================================================================
 */
#ifndef WORLD_H
#define WORLD_H

#include "graphic.h"

#define MAX_ENTITY 20

/* 
 * Clients of world need to know details about world components.
 */
typedef enum {
	NONE = 0,
	GRAPHIC = 1<<0
} component_type;

/*
 * The world is a struct of arrays of all the component structs.  This is not
 * very memory effecient, but it is easy to code!
 */
struct world {
	int mask[MAX_ENTITY];
	graphic graphics[MAX_ENTITY];
};

typedef struct world world;

extern world *world_new(void);
extern void world_free(world *);
extern int create_entity(world *);
extern int create_entity_with_graphic(world *, char *);
extern void delete_entity(world *, int);

#endif
