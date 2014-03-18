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


		// collision detection
		for (int i = 0; i < collision_components.size()-1; i++) {
			for (int j = i+1; j < collision_components.size(); j++) {
				Entity* e1 = collision_components[i]->owner;
				Entity* e2 = collision_components[j]->owner;

				Shape* s1 = ((Shape*) e1->getComponent(Component::SHAPE));
				Shape* s2 = ((Shape*) e2->getComponent(Component::SHAPE));

				// separating axis theorem
				
				// transform shape to world space
				s1->vertices[0] += e1->x;
				s1->vertices[1] += e1->y;
				s1->vertices[3] += e1->x; 
			   	s1->vertices[4] += e1->y;
				s1->vertices[6] += e1->x;
				s1->vertices[7] += e1->y;
				s1->vertices[9] += e1->x;
				s1->vertices[10] += e1->y;	

				s2->vertices[0] += e2->x;
				s2->vertices[1] += e2->y;
				s2->vertices[3] += e2->x; 
			   	s2->vertices[4] += e2->y;
				s2->vertices[6] += e2->x;
				s2->vertices[7] += e2->y;
				s2->vertices[9] += e2->x;
				s2->vertices[10] += e2->y;	

				// calculate the 4 axis
				float a1x = s1->vertices[3] - s1->vertices[0]; // Axis1.x = A.UR.x - A.UL.x
				float a1y = s1->vertices[4] - s1->vertices[1]; // Axis1.y = A.UR.y - A.UL.y

				float a2x = s1->vertices[3] - s1->vertices[6]; // Axis2.x = A.UR.x - A.LR.x
				float a2y = s1->vertices[4] - s1->vertices[7]; // Axis2.y = A.UR.y - A.LR.y
				
				float a3x = s2->vertices[0] - s2->vertices[9]; // Axis3.x = B.UL.x - B.LL.x
				float a3y = s2->vertices[1] - s2->vertices[10]; // Axis3.y = B.UL.y - B.LL.y
				
				float a4x = s2->vertices[0] - s2->vertices[3]; // Axis4.x = B.UL.x - B.UR.x
				float a4y = s2->vertices[1] - s2->vertices[4]; // Axis4.y = B.UL.y - B.UR.y
				
				// calculate projections
				
				// axis 1
				// A.UL
				float paa1ul = (s1->vertices[0] * a1x + s1->vertices[1] * a1y) / (a1x*a1x + a1y * a1y);
				float paa1ulx = paa1ul * a1x;
				float paa1uly = paa1ul * a1y;

				// A.UR
				float paa1ur = (s1->vertices[3] * a1x + s1->vertices[4] * a1y) / (a1x*a1x + a1y * a1y);
				float paa1urx = paa1ur * a1x;
				float paa1ury = paa1ur * a1y;

				// A.LR
				float paa1lr = (s1->vertices[6] * a1x + s1->vertices[7] * a1y) / (a1x*a1x + a1y * a1y);
				float paa1lrx = paa1lr * a1x;
				float paa1lry = paa1lr * a1y;

				// A.LL
				float paa1ll = (s1->vertices[9] * a1x + s1->vertices[10] * a1y) / (a1x*a1x + a1y * a1y);
				float paa1llx = paa1ll * a1x;
				float paa1lly = paa1ll * a1y;
				

				// B.UL
				float pba1ul = (s2->vertices[0] * a1x + s2->vertices[1] * a1y) / (a1x*a1x + a1y * a1y);
				float pba1ulx = pba1ul * a1x;
				float pba1uly = pba1ul * a1y;

				// B.UR
				float pba1ur = (s2->vertices[3] * a1x + s2->vertices[4] * a1y) / (a1x*a1x + a1y * a1y);
				float pba1urx = pba1ur * a1x;
				float pba1ury = pba1ur * a1y;

				// B.LR
				float pba1lr = (s2->vertices[6] * a1x + s2->vertices[7] * a1y) / (a1x*a1x + a1y * a1y);
				float pba1lrx = pba1lr * a1x;
				float pba1lry = pba1lr * a1y;

				// B.LL
				float pba1ll = (s2->vertices[9] * a1x + s2->vertices[10] * a1y) / (a1x*a1x + a1y * a1y);
				float pba1llx = pba1ll * a1x;
				float pba1lly = pba1ll * a1y;
				
				
				// axis 2
				// A.UL
				float paa2ul = (s1->vertices[0] * a2x + s1->vertices[1] * a2y) / (a2x*a2x + a2y * a2y);
				float paa2ulx = paa2ul * a2x;
				float paa2uly = paa2ul * a2y;

				// A.UR
				float paa2ur = (s1->vertices[3] * a2x + s1->vertices[4] * a2y) / (a2x*a2x + a2y * a2y);
				float paa2urx = paa2ur * a2x;
				float paa2ury = paa2ur * a2y;

				// A.LR
				float paa2lr = (s1->vertices[6] * a2x + s1->vertices[7] * a2y) / (a2x*a2x + a2y * a2y);
				float paa2lrx = paa2lr * a2x;
				float paa2lry = paa2lr * a2y;

				// A.LL
				float paa2ll = (s1->vertices[9] * a2x + s1->vertices[10] * a2y) / (a2x*a2x + a2y * a2y);
				float paa2llx = paa2ll * a2x;
				float paa2lly = paa2ll * a2y;
				

				// B.UL
				float pba2ul = (s2->vertices[0] * a2x + s2->vertices[1] * a2y) / (a2x*a2x + a2y * a2y);
				float pba2ulx = pba2ul * a2x;
				float pba2uly = pba2ul * a2y;

				// B.UR
				float pba2ur = (s2->vertices[3] * a2x + s2->vertices[4] * a2y) / (a2x*a2x + a2y * a2y);
				float pba2urx = pba2ur * a2x;
				float pba2ury = pba2ur * a2y;

				// B.LR
				float pba2lr = (s2->vertices[6] * a2x + s2->vertices[7] * a2y) / (a2x*a2x + a2y * a2y);
				float pba2lrx = pba2lr * a2x;
				float pba2lry = pba2lr * a2y;

				// B.LL
				float pba2ll = (s2->vertices[9] * a2x + s2->vertices[10] * a2y) / (a2x*a2x + a2y * a2y);
				float pba2llx = pba2ll * a2x;
				float pba2lly = pba2ll * a2y;
				

				// axis 3
				// A.UL
				float paa3ul = (s1->vertices[0] * a3x + s1->vertices[1] * a3y) / (a3x*a3x + a3y * a3y);
				float paa3ulx = paa3ul * a3x;
				float paa3uly = paa3ul * a3y;

				// A.UR
				float paa3ur = (s1->vertices[3] * a3x + s1->vertices[4] * a3y) / (a3x*a3x + a3y * a3y);
				float paa3urx = paa3ur * a3x;
				float paa3ury = paa3ur * a3y;

				// A.LR
				float paa3lr = (s1->vertices[6] * a3x + s1->vertices[7] * a3y) / (a3x*a3x + a3y * a3y);
				float paa3lrx = paa3lr * a3x;
				float paa3lry = paa3lr * a3y;

				// A.LL
				float paa3ll = (s1->vertices[9] * a3x + s1->vertices[10] * a3y) / (a3x*a3x + a3y * a3y);
				float paa3llx = paa3ll * a3x;
				float paa3lly = paa3ll * a3y;
				

				// B.UL
				float pba3ul = (s2->vertices[0] * a3x + s2->vertices[1] * a3y) / (a3x*a3x + a3y * a3y);
				float pba3ulx = pba3ul * a3x;
				float pba3uly = pba3ul * a3y;

				// B.UR
				float pba3ur = (s2->vertices[3] * a3x + s2->vertices[4] * a3y) / (a3x*a3x + a3y * a3y);
				float pba3urx = pba3ur * a3x;
				float pba3ury = pba3ur * a3y;

				// B.LR
				float pba3lr = (s2->vertices[6] * a3x + s2->vertices[7] * a3y) / (a3x*a3x + a3y * a3y);
				float pba3lrx = pba3lr * a3x;
				float pba3lry = pba3lr * a3y;

				// B.LL
				float pba3ll = (s2->vertices[9] * a3x + s2->vertices[10] * a3y) / (a3x*a3x + a3y * a3y);
				float pba3llx = pba3ll * a3x;
				float pba3lly = pba3ll * a3y;
				
				
				// axis 4
				// A.UL
				float paa4ul = (s1->vertices[0] * a4x + s1->vertices[1] * a4y) / (a4x*a4x + a4y * a4y);
				float paa4ulx = paa4ul * a4x;
				float paa4uly = paa4ul * a4y;

				// A.UR
				float paa4ur = (s1->vertices[3] * a4x + s1->vertices[4] * a4y) / (a4x*a4x + a4y * a4y);
				float paa4urx = paa4ur * a4x;
				float paa4ury = paa4ur * a4y;

				// A.LR
				float paa4lr = (s1->vertices[6] * a4x + s1->vertices[7] * a4y) / (a4x*a4x + a4y * a4y);
				float paa4lrx = paa4lr * a4x;
				float paa4lry = paa4lr * a4y;

				// A.LL
				float paa4ll = (s1->vertices[9] * a4x + s1->vertices[10] * a4y) / (a4x*a4x + a4y * a4y);
				float paa4llx = paa4ll * a4x;
				float paa4lly = paa4ll * a4y;
				

				// B.UL
				float pba4ul = (s2->vertices[0] * a4x + s2->vertices[1] * a4y) / (a4x*a4x + a4y * a4y);
				float pba4ulx = pba4ul * a4x;
				float pba4uly = pba4ul * a4y;

				// B.UR
				float pba4ur = (s2->vertices[3] * a4x + s2->vertices[4] * a4y) / (a4x*a4x + a4y * a4y);
				float pba4urx = pba4ur * a4x;
				float pba4ury = pba4ur * a4y;

				// B.LR
				float pba4lr = (s2->vertices[6] * a4x + s2->vertices[7] * a4y) / (a4x*a4x + a4y * a4y);
				float pba4lrx = pba4lr * a4x;
				float pba4lry = pba4lr * a4y;

				// B.LL
				float pba4ll = (s2->vertices[9] * a4x + s2->vertices[10] * a4y) / (a4x*a4x + a4y * a4y);
				float pba4llx = pba4ll * a4x;
				float pba4lly = pba4ll * a4y;


				// calculate projected scalar values

				// axis 1
				float psaa1ul = paa1ulx * a1x + paa1uly * a1y;
				float psaa1ur = paa1urx * a1x + paa1ury * a1y;
				float psaa1lr = paa1lrx * a1x + paa1lry * a1y;
				float psaa1ll = paa1llx * a1x + paa1lly * a1y;

				float psba1ul = pba1ulx * a1x + pba1uly * a1y;
				float psba1ur = pba1urx * a1x + pba1ury * a1y;
				float psba1lr = pba1lrx * a1x + pba1lry * a1y;
				float psba1ll = pba1llx * a1x + pba1lly * a1y;


				// axis 2
				float psaa2ul = paa2ulx * a2x + paa2uly * a2y;
				float psaa2ur = paa2urx * a2x + paa2ury * a2y;
				float psaa2lr = paa2lrx * a2x + paa2lry * a2y;
				float psaa2ll = paa2llx * a2x + paa2lly * a2y;

				float psba2ul = pba2ulx * a2x + pba2uly * a2y;
				float psba2ur = pba2urx * a2x + pba2ury * a2y;
				float psba2lr = pba2lrx * a2x + pba2lry * a2y;
				float psba2ll = pba2llx * a2x + pba2lly * a2y;


				// axis 3
				float psaa3ul = paa3ulx * a3x + paa3uly * a3y;
				float psaa3ur = paa3urx * a3x + paa3ury * a3y;
				float psaa3lr = paa3lrx * a3x + paa3lry * a3y;
				float psaa3ll = paa3llx * a3x + paa3lly * a3y;

				float psba3ul = pba3ulx * a3x + pba3uly * a3y;
				float psba3ur = pba3urx * a3x + pba3ury * a3y;
				float psba3lr = pba3lrx * a3x + pba3lry * a3y;
				float psba3ll = pba3llx * a3x + pba3lly * a3y;


				// axis 4
				float psaa4ul = paa4ulx * a4x + paa4uly * a4y;
				float psaa4ur = paa4urx * a4x + paa4ury * a4y;
				float psaa4lr = paa4lrx * a4x + paa4lry * a4y;
				float psaa4ll = paa4llx * a4x + paa4lly * a4y;

				float psba4ul = pba4ulx * a4x + pba4uly * a4y;
				float psba4ur = pba4urx * a4x + pba4ury * a4y;
				float psba4lr = pba4lrx * a4x + pba4lry * a4y;
				float psba4ll = pba4llx * a4x + pba4lly * a4y;

				
				// find min and max projected scalar

				// axis 1
				float minaa1 = psaa1ul;

				if (minaa1 > psaa1ur) 
					minaa1 = psaa1ur;
	
				if (minaa1 > psaa1lr)
					minaa1 = psaa1lr;

				if (minaa1 > psaa1ll)
					minaa1 = psaa1ll;


				float minba1 = psba1ul;

				if (minba1 > psba1ur) 
					minba1 = psba1ur;
	
				if (minba1 > psba1lr)
					minba1 = psba1lr;

				if (minba1 > psba1ll)
					minba1 = psba1ll;


				float maxaa1 = psaa1ul;

				if (maxaa1 < psaa1ur) 
					maxaa1 = psaa1ur;
	
				if (maxaa1 < psaa1lr)
					maxaa1 = psaa1lr;

				if (maxaa1 < psaa1ll)
					maxaa1 = psaa1ll;

				
				float maxba1 = psba1ul;

				if (maxba1 < psba1ur) 
					maxba1 = psba1ur;
	
				if (maxba1 < psba1lr)
					maxba1 = psba1lr;

				if (maxba1 < psba1ll)
					maxba1 = psba1ll;


				// axis 2
				float minaa2 = psaa2ul;

				if (minaa2 > psaa2ur) 
					minaa2 = psaa2ur;
	
				if (minaa2 > psaa2lr)
					minaa2 = psaa2lr;

				if (minaa2 > psaa2ll)
					minaa2 = psaa2ll;


				float minba2 = psba2ul;

				if (minba2 > psba2ur) 
					minba2 = psba2ur;
	
				if (minba2 > psba2lr)
					minba2 = psba2lr;

				if (minba2 > psba2ll)
					minba2 = psba2ll;


				float maxaa2 = psaa2ul;

				if (maxaa2 < psaa2ur) 
					maxaa2 = psaa2ur;
	
				if (maxaa2 < psaa1lr)
					maxaa2 = psaa2lr;

				if (maxaa2 < psaa2ll)
					maxaa2 = psaa2ll;

				
				float maxba2 = psba2ul;

				if (maxba2 < psba2ur) 
					maxba2 = psba2ur;

				if (maxba2 < psba2lr)
					maxba2 = psba2lr;

				if (maxba2 < psba2ll)
					maxba2 = psba2ll;


				// axis 3
				float minaa3 = psaa3ul;

				if (minaa3 > psaa3ur) 
					minaa3 = psaa3ur;
	
				if (minaa3 > psaa3lr)
					minaa3 = psaa3lr;

				if (minaa3 > psaa3ll)
					minaa3 = psaa3ll;


				float minba3 = psba3ul;

				if (minba3 > psba3ur) 
					minba3 = psba3ur;
	
				if (minba3 > psba3lr)
					minba3 = psba3lr;

				if (minba3 > psba3ll)
					minba3 = psba3ll;


				float maxaa3 = psaa3ul;

				if (maxaa3 < psaa3ur) 
					maxaa3 = psaa3ur;
	
				if (maxaa3 < psaa3lr)
					maxaa3 = psaa3lr;

				if (maxaa3 < psaa3ll)
					maxaa3 = psaa3ll;

				
				float maxba3 = psba3ul;

				if (maxba3 < psba3ur) 
					maxba3 = psba3ur;
	
				if (maxba3 < psba3lr)
					maxba3 = psba3lr;

				if (maxba3 < psba3ll)
					maxba3 = psba3ll;


				// axis 4
				float minaa4 = psaa4ul;

				if (minaa4 > psaa4ur) 
					minaa4 = psaa4ur;
	
				if (minaa4 > psaa4lr)
					minaa4 = psaa4lr;

				if (minaa4 > psaa4ll)
					minaa4 = psaa4ll;


				float minba4 = psba4ul;

				if (minba4 > psba4ur) 
					minba4 = psba4ur;
	
				if (minba4 > psba4lr)
					minba4 = psba4lr;

				if (minba4 > psba4ll)
					minba4 = psba4ll;


				float maxaa4 = psaa4ul;

				if (maxaa4 < psaa4ur) 
					maxaa4 = psaa4ur;
	
				if (maxaa4 < psaa4lr)
					maxaa4 = psaa4lr;

				if (maxaa4 < psaa4ll)
					maxaa4 = psaa4ll;

				
				float maxba4 = psba4ul;

				if (maxba4 < psba4ur) 
					maxba4 = psba4ur;
	
				if (maxba4 < psba4lr)
					maxba4 = psba4lr;

				if (maxba4 < psba1ll)
					maxba4 = psba4ll;

				
				// finally, check for collision
				bool collision = true;

				collision = collision && minba1 <= minaa4;
				collision = collision && maxba1 >= minaa4;

				collision = collision && minba2 <= minaa4;
				collision = collision && maxba2 >= minaa4;

				collision = collision && minba3 <= minaa4;
				collision = collision && maxba3 >= minaa4;

				collision = collision && minba4 <= minaa4;
				collision = collision && maxba4 >= minaa4;

				if (collision == true)
					std::cout << "Colliding!\n";
				
				// transform shape to object space
				s1->vertices[0] -= e1->x;
				s1->vertices[1] -= e1->y;
				s1->vertices[3] -= e1->x; 
			   	s1->vertices[4] -= e1->y;
				s1->vertices[6] -= e1->x;
				s1->vertices[7] -= e1->y;
				s1->vertices[9] -= e1->x;
				s1->vertices[10] -= e1->y;	

				s2->vertices[0] -= e2->x;
				s2->vertices[1] -= e2->y;
				s2->vertices[3] -= e2->x; 
			   	s2->vertices[4] -= e2->y;
				s2->vertices[6] -= e2->x;
				s2->vertices[7] -= e2->y;
				s2->vertices[9] -= e2->x;
				s2->vertices[10] -= e2->y;	
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
