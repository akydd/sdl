/*
 * ===================================================================
 *
 *       Filename:  renderer.h
 *
 *    Description:  Render system interface
 *
 *        Version:  1.0
 *        Created:  11/11/2013 06:55:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * ===================================================================
 */
#ifndef RENDERER_H
#define RENDERER_H

#include "world.h"
#include "cache.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct renderer renderer;

extern renderer *renderer_new();
extern void renderer_free(renderer *);
extern void renderer_render(renderer *, world *, cache *);

#endif
