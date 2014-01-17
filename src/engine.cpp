#include "engine.h"

Engine::Engine() {
	quit = true;

	window = NULL;
}

Engine::~Engine() {
	delete frame[0];
	delete frame[1];
	delete player;
	delete ball;
	
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(glcontext);
	SDL_Quit();
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

	frame[0] = new Rect(0, 0,  640, 16);
	frame[1] = new Rect(0, 464, 640, 16);

	player = new Rect(32, 32, 16, 64, 200);
	ball = new Rect(312, 232, 16, 16, 200);

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

	Vector2f* paddleDirection = new Vector2f(0, 0);
	Vector2f* ballDirection = new Vector2f(-1, 0);

	player->setDirection(paddleDirection);

	Uint32 old_time, current_time;
	float dt;

	current_time = SDL_GetTicks();

	while (!quit) {
		old_time = current_time;
		current_time = SDL_GetTicks();
		dt = (current_time - old_time) / 1000.0f;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				exit();

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_w:
						paddleDirection->y = -1;
						break;

					case SDLK_DOWN:
					case SDLK_s:
						paddleDirection->y = 1;
						break;

					case SDLK_SPACE:
						ball->setDirection(ballDirection);
						break;
						
				}
			}

			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_DOWN:
					case SDLK_w:
					case SDLK_s:
						paddleDirection->y = 0;
						break;
				}
			}
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
	
		if (player->intersects(frame[0]) == 1)
			player->move(0, 1);

		if (player->intersects(frame[1]) == 1)
			player->move(0, -1);

		if (player->intersects(ball) == 1)
			ballDirection->x = 1;	

		player->update(dt);
		ball->update(dt);
		
		player->render();
		ball->render();
		frame[0]->render();
		frame[1]->render();

		SDL_GL_SwapWindow(window);
	}

	delete paddleDirection;
	delete ballDirection;

}

void Engine::exit() {
	quit = true;
}
