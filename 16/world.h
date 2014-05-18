/*
 * =================================================================
 *
 *       Filename:  world.h
 *
 *    Description:  Essentially this is the Entity Manager part of the total
 *    Entity Component System.
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
#include "position.h"
#include "size.h"
#include "color.h"
#include "line.h"
#include "sprite.h"
#include "animated_sprite.h"
#include "rotation.h"
#include "text.h"

#define MAX_ENTITY 20

/* 
 * Clients of world need to know details about world components.
 */
typedef enum {
	NONE = 0,
	GRAPHIC = 1<<0,
	POSITION = 1<<1,
	SIZE = 1<<2,
	POINT = 1<<3,
	LINE = 1<<4,
	RECT = 1<<5,
	COLOR = 1<<6,
	OUTLINE_COLOR = 1<<7,
	SPRITE = 1<<8,
	ANIMATED_SPRITE = 1<<9,
	ROTATION = 1<<10,
	TEXT = 1<<11
} component_type;

/*
 * The world is a struct of arrays of all the component structs.  This is not
 * very memory effecient, but it is easy to code!
 */
struct world {
	int mask[MAX_ENTITY];
	graphic graphics[MAX_ENTITY];
	position positions[MAX_ENTITY];
	size sizes[MAX_ENTITY];
	line lines[MAX_ENTITY];
	color colors[MAX_ENTITY];
	color outline_colors[MAX_ENTITY];
	sprite sprites[MAX_ENTITY];
	animated_sprite animated_sprites[MAX_ENTITY];
	rotation rotations[MAX_ENTITY];
	text texts[MAX_ENTITY];
};

typedef struct world world;

extern world *world_new(void);
extern void world_free(world *);

// Entity management
extern int world_create_entity(world *);
extern void world_delete_entity(world *, int);
extern void world_delete_all_entities(world *);

// Graphic component
extern void world_add_graphic_component(world *, int, char *);
extern void world_remove_graphic_component(world *, int);

// Position component
extern void world_add_position_component(world *, int, int, int);
extern void world_remove_position_component(world *, int);

// Size component
extern void world_add_size_component(world *, int, int, int);
extern void world_remove_size_component(world *, int);

// Color component
extern void world_add_color_component(world *, int, int, int, int, int);
extern void world_remove_color_component(world *, int);

// Outline Color component
extern void world_add_outline_color_component(world *, int, int, int, int, int);
extern void world_remove_outline_color_component(world *, int);

// Point component
extern void world_add_point_component(world *, int);
extern void world_remove_point_component(world *, int);

// Line component
extern void world_add_line_component(world *, int, int, int, int, int);
extern void world_remove_line_component(world *, int);

// Rectangle component
extern void world_add_rectangle_component(world *, int);
extern void world_remove_rectangle_component(world *, int);

// Sprite component
extern void world_add_sprite_component(world *, int, int, int, int, int);
extern void world_remove_sprite_component(world *, int);

// Animated sprite component
extern void world_add_animated_sprite_component(world *, int, char *, int, ...);
extern void world_remove_animated_sprite_component(world *, int);

// Rotation component
extern void world_add_rotation_component(world *, int, double, int, int, int);
extern void world_remove_rotation_component(world *, int);

// Text component
extern void world_add_text_component(world *, int, char *, char *, int, int, int, int, int, int);
extern void world_remove_text_component(world *, int);

#endif
