#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv)
{
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		(void)printf("SDL could not init: %s\n", SDL_GetError());
	} else {
		window = SDL_CreateWindow("C Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			(void)printf("Window could not be created! %s\n", SDL_GetError());
		} else {
			surface = SDL_GetWindowSurface(window);
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
