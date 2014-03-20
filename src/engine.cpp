#include "engine.h"

#include <math.h>

static const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

namespace JEngine {

	Engine::Engine() {
		run = false;
		window = NULL;
	}

	Engine::~Engine() {
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

		objects = new GameObjects();
		system = new System(objects);

		systems.push_back(new MovementSystem(objects));
		systems.push_back(new CollisionSystem(objects));
		systems.push_back(new RenderSystem(objects, window));

		player = system->pushEntity(new Entity(100.0f, 100.0f, 0.0f));

		system->attachComponent(player, new Shape({
			-16.0f, -16.0f, 0.0f,
			16.0f, -16.0f, 0.0f,
			16.0f, 16.0f, 0.0f,
			-16.0f, 16.0f, 0.0f		
		}));

		system->attachComponent(player, new Velocity(0.0f, 0.0f, 0.0f, 1000.0f, 1000.0f, 400.0f));
		system->attachComponent(player, new Direction(1.0f, 0.0f, 0.0f));
		system->attachComponent(player, new Collision(Collision::RIGID_BODY));

		int target = system->pushEntity(new Entity(200.0f, 200.0f, 0.0f));
	
		system->attachComponent(target, new Shape({
			-16.0f, -16.0f, 0.0f,
			16.0f, -16.0f, 0.0f,
			16.0f, 16.0f, 0.0f,
			-16.0f, 16.0f, 0.0f,
		}));
	
		system->attachComponent(target, new Collision(Collision::RIGID_BODY));

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
				case SDLK_w: 	
					input_w = true;
					break;

				case SDLK_s:
					input_s = true;
					break;

				case SDLK_a:
					input_a = true;
					break;

				case SDLK_d:
					input_d = true;
					break;
			}
		}

		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
				case SDLK_w:
					input_w = false;
					break;

				case SDLK_s:
					input_s = false;
					break;

				case SDLK_a:
					input_a = false;
					break;

				case SDLK_d:
					input_d = false;
					break;

				case SDLK_f:
					Entity* t = system->getEntity(player);
					
					Direction* d = new Direction(1.0f, 0.0f, 0.0f);

					int x, y;
					SDL_GetMouseState(&x, &y);

					float angle = atan2(t->y-y, t->x-x);
					angle += PI;
					d->setRotation(angle);

					int projectile = system->pushEntity(new Entity(t->x + d->x*40, t->y + d->y*40, t->z + d->z*40));
					system->attachComponent(projectile, d);
						
					system->attachComponent(projectile, new Shape({
						-4.0f, -4.0f, 0.0f,
						4.0f, -4.0f, 0.0f,
						4.0f, 4.0f, 0.0f,
						-4.0f, 4.0f, 0.0f		
					}));

					system->attachComponent(projectile, new Velocity(1000.0f, 1000.0f, 0.0f, 1.0f, 1.0f, 100.0f));
					system->attachComponent(projectile, new Collision(Collision::EXPLOSIVE));
				
					break;
			}
		}

		
		if (e.type == SDL_MOUSEMOTION) {
			SDL_MouseMotionEvent motion = e.motion;
			Entity* t = system->getEntity(player);

			float angle = atan2(t->y-e.motion.y, t->x-e.motion.x);
			angle += PI;

			((Direction*) system->getComponent(Component::DIRECTION, t->components[Component::DIRECTION]));
		}
	}
	void Engine::update(float dt) {
		Entity* t = system->getEntity(player);

		Direction* d = (Direction*) system->getComponent(Component::DIRECTION, t->components[Component::DIRECTION]);
		Velocity* v = (Velocity*) system->getComponent(Component::VELOCITY, t->components[Component::VELOCITY]);
		Shape* s = (Shape*) system->getComponent(Component::SHAPE, t->components[Component::SHAPE]);

		int x, y;
		SDL_GetMouseState(&x, &y);

		double angle;
		angle = atan2(t->y-y, t->x-x);
		angle += PI;

		s->setRotation(angle);

		if (input_w || input_a || input_s || input_d) {
			d->setRotation(angle);

			if (input_a && input_s) {
				angle = -135;
			} else if (input_a && input_w) {
				angle = -45;
			} else if (input_d && input_s) {
				angle = 135;
			} else if (input_d && input_w) {
				angle = 45;
			} else if (input_a) {
				angle = -90;
			} else if (input_d) {
				angle = 90;
			} else if (input_s) {
				angle = 180;
			} else if (input_w) {
				angle = 0;
			}

			angle *= PI/180.0f; // degrees to radians;
			d->rotate(angle);

			v->x += v->acceleration*dt;
			v->y += v->acceleration*dt;

			if (v->x > v->max_speed)
				v->x = v->max_speed;

			if (v->y > v->max_speed)
				v->y = v->max_speed;

		} else {
			v->x -= v->deacceleration*dt;
			v->y -= v->deacceleration*dt;
			
			if (v->x < 0)
				v->x = 0;

			if (v->y < 0)
				v->y = 0;
		}


		for (auto it = systems.begin(); it != systems.end(); it++)
			(*it)->update(dt);
	}

	void Engine::quit() {
		run = false;
	}

	bool Engine::isRunning() {
		return run;
	}

}
