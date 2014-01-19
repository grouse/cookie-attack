#include "engine.h"

Engine::Engine() {
	quit = true;

	window = NULL;
}

Engine::~Engine() {
	delete frame[0];
	delete frame[1];
	delete player1;
	delete player2;
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

	// goal rects
	frame[2] = new Rect(-32, 0, 1, 480);
	frame[3] = new Rect(672, 0, 1, 480);

	player1 = new Rect(32, 32, 16, 64, 200);
	player2 = new Rect(592, 32, 16, 64, 200);
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

	Vector2f* player1Direction = new Vector2f(0, 0);
	Vector2f* player2Direction = new Vector2f(0, 0);
	
	Vector2f* ballDirection = new Vector2f(0, 0);
	ball->setDirection(ballDirection);

	player1->setDirection(player1Direction);
	player2->setDirection(player2Direction);

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
						player2Direction->y = -1;
						break;

					case SDLK_w:
						player1Direction->y = -1;
						break;

					case SDLK_DOWN:
						player2Direction->y = 1;
						break;

					case SDLK_s:
						player1Direction->y = 1;
						break;

					case SDLK_SPACE:
						if (ballDirection->x == 0 && ballDirection->y == 0)
							ballDirection->x = -1;
						
						break;

					case SDLK_r: 
						ball->setPos(312, 232);
						ballDirection->y = 0;
						ballDirection->x = 0;
						break;
						
				}
			}

			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
					case SDLK_DOWN:
						player2Direction->y = 0;
						break;

					case SDLK_w:
					case SDLK_s:
						player1Direction->y = 0;
						break;
				}
			}
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		player1->update(dt);
		player2->update(dt);
		ball->update(dt);
		
		Vector2f intersection = Vector2f(0,0);
		
		// paddle -> frame collisions
		if (player1->isIntersecting(frame[0]) != 0) {	
			intersection = player1->getIntersection(frame[0]);
			player1->move(intersection);
		}

		if (player1->isIntersecting(frame[1]) != 0) {	
			intersection = player1->getIntersection(frame[1]);
			player1->move(intersection);
		}

		if (player2->isIntersecting(frame[0]) != 0) {	
			intersection = player2->getIntersection(frame[0]);
			player2->move(intersection);
		}

		if (player2->isIntersecting(frame[1]) != 0) {	
			intersection = player2->getIntersection(frame[1]);
			player2->move(intersection);
		}

		// ball -> paddle collisions
		if (player1->isIntersecting(ball) != 0) {
			Vector2f playerOrigin = player1->getOrigin();
			Vector2f ballOrigin = ball->getOrigin();

			float angle = playerOrigin.angleBetween(ballOrigin);
			ballDirection->setRotation(angle);
		}	

		if (player2->isIntersecting(ball) != 0) {
			Vector2f playerOrigin = player2->getOrigin();
			Vector2f ballOrigin = ball->getOrigin();

			float angle = 3.14 + playerOrigin.angleBetween(ballOrigin);
			ballDirection->setRotation(angle);
		}

		// ball -> frame collisions
		if (ball->isIntersecting(frame[0]) != 0 || ball->isIntersecting(frame[1])) {
			ballDirection->y *= -1;
		}

		// ball -> goal collisions
		if (ball->isIntersecting(frame[2]) != 0) {
			std::cout << "player 2 scores!\n";
		
			ball->setPos(312, 232);
			ballDirection->y = 0;
			ballDirection->x = 0;
		}

		if (ball->isIntersecting(frame[3]) != 0) {
			std::cout << "player 1 scores!\n";
	
			ball->setPos(312, 232);
			ballDirection->y = 0;
			ballDirection->x = 0;
		}

		
		player1->render();
		player2->render();
		ball->render();
		frame[0]->render();
		frame[1]->render();

		SDL_GL_SwapWindow(window);
	}

	delete player1Direction;
	delete player2Direction;
	delete ballDirection;

}

void Engine::exit() {
	quit = true;
}
