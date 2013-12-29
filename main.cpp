#include "SDL2/SDL.h"
#include <iostream>

int main(int argc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Error initialising SDL\n" << SDL_GetError() << "\n";
		return -1;
	}
	
	window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);

	if (window == NULL) {
		std::cerr << "Error initialising window\n" << SDL_GetError() << "\n";
		SDL_Quit();
		return -1;
	}

	renderer = SDL_CreateRenderer(
		window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	
	);

	if (renderer == NULL) {
		std::cerr << "Error initialising renderer\n" << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}


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

	return 0;
}
