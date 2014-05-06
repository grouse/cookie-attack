#include "engine.h"

#include <math.h>


#include "stb_image.c"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>



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

		delete system;
		delete objects;
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

		systems.push_back(new LifeTimeSystem(objects));
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

		system->attachComponent(player, new Velocity(0.0f, 0.0f, 0.0f, 1000.0f, 2.0f, 400.0f));
		system->attachComponent(player, new Direction(1.0f, 0.0f, 0.0f));

		system->attachComponent(player, new Collision([] (Entity* e1, Entity* e2) {
			//std::cout << "test\n";				
		}));

		system->attachComponent(player, new Texture("assets/ship.png"));

		Entity* target = system->pushEntity(new Entity(200.0f, 200.0f, 0.0f));
	
		system->attachComponent(target, new Shape({
			-16.0f, -16.0f, 0.0f,
			16.0f, -16.0f, 0.0f,
			16.0f, 16.0f, 0.0f,
			-16.0f, 16.0f, 0.0f,
		}));
	
		system->attachComponent(target, new Collision([] (Entity* e1, Entity* e2) {
			//std::cout << "test\n";				
		}));

		run = true;
		return 0;
	}

	void Engine::initGL(int w, int h) {
		glcontext = SDL_GL_CreateContext(window);
		
		
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		// Set viewport

		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}


	void Engine::handleInput(SDL_Event& e) {
		if (e.type == SDL_QUIT)
			quit();

		if (e.type == SDL_MOUSEMOTION) {
			Shape* s = (Shape*) player->components[Component::SHAPE];
		
			glm::vec3 mouse = glm::vec3(e.motion.x, e.motion.y, 0.0f);
			glm::vec3 direction = mouse - player->pos;
			
			float angle = atan2(direction.y, direction.x);
			s->setRotation(angle + PI/2);
		}	

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
					glm::vec3 rotation = glm::rotateZ(glm::vec3(1.0f, 0.0f, 0.0f), (float)(((Shape*) player->components[Component::SHAPE])->rotation - PI/2.0f));
					glm::vec3 pos = player->pos + rotation*25.0f;

					Entity* projectile = system->pushEntity(new Entity(pos));
						
					system->attachComponent(projectile, new Shape({
						-4.0f, -4.0f, 0.0f,
						4.0f, -4.0f, 0.0f,
						4.0f, 4.0f, 0.0f,
						-4.0f, 4.0f, 0.0f		
					}));

					system->attachComponent(projectile, new Velocity(rotation.x*1000, rotation.y*1000, 0.0f, 1.0f, 0.0f, 100.0f));
					system->attachComponent(projectile, new Collision([] (Entity* e1, Entity* e2) {
						//std::cout << "test\n";				
					}));
		
					system->attachComponent(projectile, new LifeTime(5));
				
					break;
			}
		}
	}

	void Engine::update(float dt) {

		
		Velocity* v = (Velocity*) player->components[Component::VELOCITY];
		Shape* s = (Shape*) player->components[Component::SHAPE];

		if (input_w || input_a || input_s || input_d) {
			glm::vec3 thrust;

			if (input_a && input_s) {
				thrust = glm::vec3(-1.0f, 1.0f, 0.0f);
			} else if (input_a && input_w) {
				thrust = glm::vec3(-1.0f, -1.0f, 0.0f);
			} else if (input_d && input_s) {
				thrust = glm::vec3(1.0f, 1.0f, 0.0f);
			} else if (input_d && input_w) {
				thrust = glm::vec3(1.0f, -1.0f, 0.0f);
			} else if (input_a) {
				thrust = glm::vec3(-1.0f, 0.0f, 0.0f);
			} else if (input_d) {
				thrust = glm::vec3(1.0f, 0.0f, 0.0f);
			} else if (input_s) {
				thrust = glm::vec3(0.0f, 1.0f, 0.0f);
			} else if (input_w) {
				thrust = glm::vec3(0.0f, -1.0f, 0.0f);
			}

			thrust = glm::normalize(thrust);
			thrust = glm::rotateZ(thrust, s->rotation);
	
			v->vec3 += thrust*v->acceleration*dt;

		} else {
			glm::vec3 new_v = v->vec3 - v->vec3*v->deacceleration*dt;

			/**if (glm::length(new_v) != 0) {
				glm::vec3 amount = v->vec3*v->deacceleration*dt;


				std::cout << "deacceleration: " << v->deacceleration << "\n";
				std::cout << "deacceleration amount: (" << amount.x << ", " << amount.y << ")\n";
				std::cout << "deacceleration length: " << glm::length(amount) << "\n";
				std::cout << "new velocity: (" << new_v.x << ", " << new_v.y << ")\n";
			} **/
			
			if (glm::length(new_v) >= glm::length(v->vec3)) {
				v->vec3 = glm::vec3(0.0f);
			} else {
				v->vec3 = new_v;	
			}
		}


		/**Direction* d = (Direction*) player->components[Component::DIRECTION];
		Velocity* v = (Velocity*) player->components[Component::VELOCITY];
		Shape* s = (Shape*) player->components[Component::SHAPE];

		int x, y;
		SDL_GetMouseState(&x, &y);

		double angle;
		angle = atan2(player->y-y, player->x-x);
		angle += PI;	

		s->setRotation(angle + PI/2);

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
		} **/


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
