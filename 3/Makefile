CC=gcc
CFLAGS=-Wall -Wextra -O -std=c11 -I/usr/include/SDL2
LIBFLAGS=-lSDL2


game: world.o cache.o renderer.o game.o
	$(CC) $(CFLAGS) world.o cache.o renderer.o game.o -o game $(LIBFLAGS)

game.o: world.h graphic.h cache.h renderer.h game.c
world.o: world.c world.h graphic.h
renderer.o: renderer.c renderer.h world.h cache.h
cache.o: cache.c cache.h

clean:
	rm *.o game
