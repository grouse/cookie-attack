#include "SDL2/SDL.h"
#include <iostream>

int main(int argc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	renderer = SDL_CreateRenderer(
		window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	
	);


	bool quit = false;
	SDL_Event e;

	while(!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;

			if (e.type == SDL_KEYDOWN) 
				quit = true;

			if (e.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		SDL_Delay(2000);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Working";
	return -1;
}
