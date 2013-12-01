/*
 * =====================================================================================
 *
 *       Filename:  cache.h
 *
 *    Description:  Cache of SDL_Surface
 *
 *        Version:  1.0
 *        Created:  13-11-28 10:12:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */

#ifndef CACHE_H
#define CACHE_H

#include <SDL2/SDL.h>

typedef struct cache cache;

extern cache *cache_new(void);
extern void cache_free(cache **cache);
extern SDL_Surface *cache_get(cache **cache, const char *key);

#endif
