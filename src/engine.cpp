#include "engine.h"

#include <math.h>

static const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348;

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

		Velocity* v = new Velocity(0.0f, 0.0f, 0.0f, 1000.0f, 1000.0f, 400.0f);
		player->attach(v);

		Direction* d = new Direction(1.0f, 0.0f, 0.0f);
		player->attach(d);

		Collision* c = new Collision();
		player->attach(c);
	
		collision_components.push_back(c);	

		components.push_back(v);
		components.push_back(s);
		components.push_back(d);
		entities.push_back(player);

		Entity* target = new Entity(200.0f, 200.0f, 0.0f);
		
		Shape* s2 = new Shape({
			-16.0f, -16.0f, 0.0f,
			16.0f, -16.0f, 0.0f,
			16.0f, 16.0f, 0.0f,
			-16.0f, 16.0f, 0.0f,
		});
		target->attach(s2);
		
		Collision* c2 = new Collision();
		target->attach(c2);

		collision_components.push_back(c2);
		components.push_back(s2);
		entities.push_back(target);

		
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
					Entity* projectile = new Entity(player->x, player->y, player->z);
					
					Shape* s = new Shape({
						-4.0f, -4.0f, 0.0f,
						4.0f, -4.0f, 0.0f,
						4.0f, 4.0f, 0.0f,
						-4.0f, 4.0f, 0.0f		
					});
					projectile->attach(s);
					components.push_back(s);

					Velocity* v = new Velocity(1000.0f, 1000.0f, 0.0f, 1.0f, 1.0f, 100.0f);
					projectile->attach(v);
					components.push_back(v);

					Direction* d = new Direction(1.0f, 0.0f, 0.0f);

					int x, y;
					SDL_GetMouseState(&x, &y);

					float angle = atan2(player->y-y, player->x-x);
					angle += PI;
					d->setRotation(angle);

					projectile->attach(d);
					components.push_back(d);

					entities.push_back(projectile);
					break;
			}
		}

		
		if (e.type == SDL_MOUSEMOTION) {
			SDL_MouseMotionEvent motion = e.motion;

			angle = atan2(player->y-e.motion.y, player->x-e.motion.x);
			angle += PI;

			((Direction*) player->getComponent(Component::DIRECTION))->setRotation(angle);
		}
	}
	void Engine::update(float dt) {

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Direction* d = (Direction*) player->getComponent(Component::DIRECTION);
		Velocity* v = (Velocity*) player->getComponent(Component::VELOCITY);
		Shape* s = (Shape*) player->getComponent(Component::SHAPE);

		int x, y;
		SDL_GetMouseState(&x, &y);

		double angle;
		angle = atan2(player->y-y, player->x-x);
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

		for (int i = 0; i < collision_components.size()-1; i++) {
			for (int j = i+1; j < collision_components.size(); j++) {
				Entity* e1 = collision_components[i]->owner;
				Entity* e2 = collision_components[j]->owner;

				Shape* s1 = ((Shape*) e1->getComponent(Component::SHAPE));
				Shape* s2 = ((Shape*) e2->getComponent(Component::SHAPE));
			}
		}

		for (auto it = entities.begin(); it != entities.end(); it++) {
			Entity* e = (*it);

			if (e->hasComponent(Component::VELOCITY) && e->hasComponent(Component::DIRECTION)) {
				
				Velocity* v = (Velocity*) e->getComponent(Component::VELOCITY);
				Direction* d = (Direction*) e->getComponent(Component::DIRECTION);	
								
				e->x += v->x*d->x*dt;
				e->y += v->y*d->y*dt;
				e->z += v->z*d->z*dt;
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
