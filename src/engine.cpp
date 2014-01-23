#include "engine.h"

namespace JEngine {

	Engine::Engine() {
		run = false;
		window = NULL;
	}

	Engine::~Engine() {
		delete s;
		delete v;
		delete p;

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
		
		p = new Position(0.0f, 0.0f, 0.0f);
	
		s = new Shape({
			-16.0f, -16.0f, 0.0f,
			16.0f, -16.0f, 0.0f,
			16.0f, 16.0f, 0.0f,
			-16.0f, 16.0f, 0.0f		
		});

		v = new Velocity(20.0f, 0.0f, 0.0f);

		if (!e.attach(p)) {
			std::cout << "Failed to attach position to entity\n";
			return -1;
		}

		if (!e.attach(s)) {
			std::cout << "Failed to attach shape to entity\n";
			return -1;
		}

		if (!e.attach(v)) {
			std::cout << "Failed to attach velocity to entity\n";
			return -1;
		}

		std::cout << "attached components\n";	


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
		if (e.type == SDL_QUIT)
			quit();

		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_d:
					v->rotate(0.5);
					break;

				case SDLK_a:				
					v->rotate(-0.5);
					break;		
			}
		}

		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {

			}
		}
	}

	void Engine::update(float dt) {

		p->x += v->x*dt;
		p->y += v->y*dt;
		p->z += v->z*dt;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
	
		glTranslatef(p->x, p->y, p->z);
		glColor3f(255, 255, 255);

		glVertexPointer(3, GL_FLOAT, 0, s->vertices.data());
		glDrawArrays(GL_QUADS, 0, 4);	
		
		glTranslatef(-p->x, -p->y, -p->z);

		SDL_GL_SwapWindow(window);
	}

	void Engine::quit() {
		run = false;
	}

	bool Engine::isRunning() {
		return run;
	}

}
