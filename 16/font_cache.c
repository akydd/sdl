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
	struct font_cache *next;
};

font_cache *font_cache_new(void)
{
	TTF_Init();
	return NULL;
}

void font_cache_free(font_cache **the_cache)
{
	while(*the_cache != NULL) {
		font_cache *tmp_ptr = *the_cache;
		*the_cache = tmp_ptr->next;

		free(tmp_ptr->key);
		TTF_CloseFont(tmp_ptr->value);
		free(tmp_ptr);
	}
	TTF_Quit();
}
