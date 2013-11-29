/*
 * =====================================================================================
 *
 *       Filename:  cache.c
 *
 *    Description:  Implementation of the SDL_Surface cache
 *
 *        Version:  1.0
 *        Created:  13-11-28 10:18:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "cache.h"

struct cache {
	SDL_Surface *images[CACHE_SIZE];
};

cache *cache_new() {
	cache *new_cache;
	new_cache = malloc(sizeof(cache));
	return new_cache;
}
