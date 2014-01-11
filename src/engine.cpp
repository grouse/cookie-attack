#include "engine.h"


#include "rect.h"

#include <iostream>

Engine::Engine() {
	quit = true;

	window = NULL;
	renderer = NULL;
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

	initGL(640, 480);

	frame = new Rect*[2];
	frame[0] = new Rect(0, 0,  640, 16, 0);
	frame[1] = new Rect(0, 464, 640, 16, 0);

	player = new Rect(32, 32, 16, 64, 1);

	quit = false;

	return 0;
}

void Engine::initGL(int w, int h) {
	glcontext = SDL_GL_CreateContext(window);
	
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Set viewport

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Engine::run() {
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				exit();

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_w:
						player->move(Rect::NONE, Rect::UP);
						break;

					case SDLK_DOWN:
					case SDLK_s:
						player->move(Rect::NONE, Rect::DOWN);
						break;
						
				}
			}

			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_DOWN:
					case SDLK_w:
					case SDLK_s:
						player->move(Rect::NONE, Rect::NONE);
						break;
				}
			}
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
	
		frame[0]->render();
		frame[1]->render();


		if (player->intersects(frame[0]) == 1)
			player->move(0, 1);

		if (player->intersects(frame[1]) == 1) {
			player->move(0, -1);
		}

		player->update();
		player->render();

		SDL_GL_SwapWindow(window);
		SDL_RenderPresent(renderer);
	}

	delete frame[0];
	delete frame[1];
	delete[] frame;
	delete player;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	SDL_GL_DeleteContext(glcontext);
}

void Engine::exit() {
	quit = true;
}
