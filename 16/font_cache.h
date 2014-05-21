/*
 * =====================================================================================
 *
 *       Filename:  font_cache.h
 *
 *    Description:  Cache for TTF_Font
 *
 *        Version:  1.0
 *        Created:  14-01-04 10:39:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd
 *
 * =====================================================================================
 */

#ifndef FONT_CACHE_H
#define FONT_CACHE_H

#include <SDL2/SDL_ttf.h>

typedef struct font_cache font_cache;

extern font_cache *font_cache_new(void);
extern void font_cache_free(font_cache **);
extern TTF_Font *font_cache_get(font_cache ** const, const char *, const int);

#endif
