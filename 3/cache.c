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
#include <string.h>

#include "cache.h"

struct cache {
	char *key;
	SDL_Texture *value;
	struct cache *next;
};

cache *cache_new(void)
{
	return NULL;
}

void cache_free(cache **the_cache)
{
	while(*the_cache != NULL) {
		cache *tmp_ptr = *the_cache;
		*the_cache = tmp_ptr->next;

		free(tmp_ptr->key);
		SDL_DestroyTexture(tmp_ptr->value);
		free(tmp_ptr);
	}
}

SDL_Texture *cache_get(cache **the_cache, SDL_Renderer *sdl_renderer, const char *key)
{
	// search for key and return value if found
	for(cache *search_ptr = *the_cache; search_ptr; search_ptr = search_ptr->next) {
		if(strcmp(key, search_ptr->key) == 0) {
			return search_ptr->value;
		}
	}

	// store new entry in cache and return it
	cache *new_entry = malloc(sizeof(cache));
	new_entry->key = malloc(sizeof(char) * (strlen(key) + 1));
	(void)strcpy(new_entry->key, key);

	SDL_Surface *surface = SDL_LoadBMP(key);
	new_entry->value = SDL_CreateTextureFromSurface(sdl_renderer, surface);
	SDL_FreeSurface(surface);

	new_entry->next = *the_cache;
	*the_cache = new_entry;	

	return new_entry->value;
}
