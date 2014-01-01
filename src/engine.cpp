#include "engine.h"

Engine::Engine() {
	quit = true;
}

Engine::~Engine() {

}

int Engine::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << SDL_GetError() << "\n";
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
		std::cerr << SDL_GetError() << "\n";
		SDL_Quit();
		return -1;
	}

	renderer = SDL_CreateRenderer(
		window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC		
	);

	if (renderer == NULL) {
		std::cerr << SDL_GetError() << "\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	quit = false;

	return 0;
}

void Engine::run() {
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				exit();
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Engine::exit() {
	quit = true;
}
