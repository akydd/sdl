/*
 * =====================================================================================
 *
 *       Filename:  font_cache.c
 *
 *    Description:  Implementation of the TTF_Font cache
 *
 *        Version:  1.0
 *        Created:  14-01-04 10:54:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

#include "font_cache.h"

struct font_cache {
	char *key;
	TTF_Font *value;
	struct cache *next;
};
