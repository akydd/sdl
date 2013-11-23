CC=gcc
CFLAGS=-Wall -Wextra -O -std=c11 -I/usr/include/SDL2
LIBFLAGS=-lSDL2


game: world.o renderer.o game.o
	$(CC) $(CFLAGS) world.o renderer.o game.o -o game $(LIBFLAGS)

game.o: world.h graphic.h game.c
world.o: world.c world.h graphic.h
renderer.o: renderer.c renderer.h world.h

clean:
	rm *.o game
