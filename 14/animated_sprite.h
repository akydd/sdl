/*
 * =====================================================================================
 *
 *       Filename:  animated_sprite.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13-12-16 10:37:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

typedef struct {
	// Contains the filename of the spritesheet
	char *image_file;
	// A variable sized array of sprite structs
	sprite *sprites;
} animated_sprite;

#endif
