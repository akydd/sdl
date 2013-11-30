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
#include "table.h"

struct cache {
	table *table;;
};

cache *cache_new()
{
	cache *new_cache;
	new_cache = malloc(sizeof(cache));
	new_cache->table = table_new();
	return new_cache;
}

void cache_free(cache *cache)
{

}

SDL_Surface *cache_get(cache *cache, const char *key)
{
	return table_get(&cache->table, key);
}

void cache_put(cache *cache, const char *key, const SDL_Surface *surface)
{
	table_put(&cache->table, key, surface);
}
