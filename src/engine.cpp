#include "engine.h"

#include <math.h>


namespace JEngine {

	Engine::Engine() {
		run = false;
		window = NULL;
	}

	Engine::~Engine() {
		for (auto it = components.begin(); it != components.end(); it++) 
			delete (*it);
		
		for (auto it = entities.begin(); it != entities.end(); it++) 
			delete (*it);

		SDL_DestroyWindow(window);
		SDL_GL_DeleteContext(glcontext);
		SDL_Quit();
	}

	int Engine::init(const char* title, int w, int h) {

		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cerr << SDL_GetError() << "\n";
			return -1;
		}

		window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			w,
			h,
			SDL_WINDOW_OPENGL		
		);

		if (window == NULL) {
			std::cerr << SDL_GetError() << "\n";
			SDL_Quit();
			return -1;
		}

		initGL(w, h);

		player = new Entity(100.0f, 100.0f, 0.0f);

		Shape* s = new Shape({
			-16.0f, -16.0f, 0.0f,
			16.0f, -16.0f, 0.0f,
			16.0f, 16.0f, 0.0f,
			-16.0f, 16.0f, 0.0f		
		});
		player->attach(s);

		Velocity* v = new Velocity(0.0f, 0.0f, 0.0f);
		player->attach(v);

		components.push_back(v);
		components.push_back(s);
		entities.push_back(player);

		
	//	s->rotate(0.785398163);

		run = true;
		return 0;
	}

	void Engine::initGL(int w, int h) {
		glcontext = SDL_GL_CreateContext(window);
		
		
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnableClientState(GL_VERTEX_ARRAY);


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


	void Engine::handleInput(SDL_Event& e) {
		float angle;
		Velocity* v;

		if (e.type == SDL_QUIT)
			quit();

		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_SPACE: 	
					int x, y;
					SDL_GetMouseState(&x, &y);

					angle = atan2(y-player->y, x-player->x);
					v = (Velocity*) player->getComponent(Component::VELOCITY);

					v->x = cos(angle);
					v->y = sin(angle);
					break;

				case SDLK_w:
					rotation = true;
					break;
			}
		}

		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
				case SDLK_SPACE:
					Velocity* v = (Velocity*) player->getComponent(Component::VELOCITY);
					v->x = 0;
					v->y = 0;
					break;
			}
		}

		
		if (e.type == SDL_MOUSEMOTION && rotation == true) {
			SDL_MouseMotionEvent motion = e.motion;

			angle = atan2(player->y-e.motion.y, player->x-e.motion.x);
			((Shape*) player->getComponent(Component::SHAPE))->setRotation(angle);
		}
	}
	void Engine::update(float dt) {

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (auto it = entities.begin(); it != entities.end(); it++) {
			Entity* e = (*it);

			if (e->hasComponent(Component::VELOCITY)) {
				Velocity* v = (Velocity*) e->getComponent(Component::VELOCITY);
				e->x += v->x*dt*100;
				e->y += v->y*dt*100;
				e->z += v->z*dt*100;
			}

			if (e->hasComponent(Component::SHAPE)) {

				glLoadIdentity();

				glTranslatef(e->x, e->y, e->z);
				glColor3f(255, 255, 255);
				
				Shape* s = (Shape*) e->getComponent(Component::SHAPE);

				glVertexPointer(
						3, GL_FLOAT, 0, 
						s->vertices.data()
					);

				glDrawArrays(GL_QUADS, 0, 4);
				
				glTranslatef(-e->x, -e->y, -e->z);
			}
		}

		SDL_GL_SwapWindow(window);
	}

	void Engine::quit() {
		run = false;
	}

	bool Engine::isRunning() {
		return run;
	}

}
