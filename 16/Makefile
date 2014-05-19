CC=gcc
CFLAGS=-Wall -Wextra -O -std=c11 -I/usr/include/SDL2
LIBFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf


game: world.o cache.o font_cache.o renderer.o input_system.o game.o
	$(CC) $(CFLAGS) world.o cache.o font_cache.o renderer.o input_system.o game.o -o game $(LIBFLAGS)

game.o: world.h graphic.h cache.h font_cache.h renderer.h game.c
world.o: world.c world.h graphic.h position.h size.h color.h sprite.h animated_sprite.h rotation.h text.h
renderer.o: renderer.c renderer.h world.h cache.h font_cache.h
cache.o: cache.c cache.h
font_cache.o: font_cache.c font_cache.h
input_system.o: input_system.c input_system.h world.h

clean:
	rm *.o game
