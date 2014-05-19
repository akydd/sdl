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
#include <stdio.h>

#include <SDL2/SDL_ttf.h>

#include "font_cache.h"

struct font_cache_key {
    char *filename;
    int size;
};

struct font_cache {
    struct font_cache_key key;
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

		free(tmp_ptr->key.filename);
		TTF_CloseFont(tmp_ptr->value);
		free(tmp_ptr);
	}
	TTF_Quit();
}

int equal(const char *filename, const int size, struct font_cache_key key)
{
    (void)printf("Comparing new %d to existing %d\n", size, key.size);
    if (size == key.size) {
        return 1;
    }

    (void)printf("Comparing new %s to existing %s\n", filename, key.filename);
    if (strcmp(filename, key.filename) == 0) {
        return 1;
    }

    return 0;
}

TTF_Font *font_cache_get(font_cache **the_cache, const char *font, const int size)
{
    // search for existing font in cache
    for (font_cache *search_ptr = *the_cache; search_ptr; search_ptr = search_ptr->next) {
        if (equal(font, size, search_ptr->key) == 1) {
            return search_ptr->value;
        }
    }
    (void)printf("Font %s not in cache\n", font);

    // store new entry in cache and return it
    font_cache *new_entry = malloc(sizeof(font_cache));
    new_entry->key.filename = malloc(sizeof(char) * (strlen(font) + 1));
    (void)strcpy(new_entry->key.filename, font);
    new_entry->key.size = size;
    new_entry->value = malloc(sizeof(TTF_Font));
    new_entry->value = TTF_OpenFont(font, size);

    new_entry->next = *the_cache;
    *the_cache = new_entry;

    return new_entry->value;
}

