CC=gcc
CFLAGS=-Wall -Wextra -O -std=c11 -I/usr/include/SDL2
LIBFLAGS=-lSDL2 -lSDL2_image


game: world.o cache.o renderer.o input_system.o game.o
	$(CC) $(CFLAGS) world.o cache.o renderer.o input_system.o game.o -o game $(LIBFLAGS)

game.o: world.h graphic.h cache.h renderer.h game.c
world.o: world.c world.h graphic.h position.h size.h color.h sprite.h animated_sprite.h
renderer.o: renderer.c renderer.h world.h cache.h
cache.o: cache.c cache.h
input_system.o: input_system.c input_system.h world.h

clean:
	rm *.o game
