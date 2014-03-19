#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <list>
#include <vector>

#include "entity.h"
#include "component.h"
#include "shape.h"
#include "velocity.h"
#include "direction.h"
#include "collision.h"

namespace JEngine {
	class Engine {
		public:
			Engine();
			virtual ~Engine();

			int init(const char*, int, int);

			void handleInput(SDL_Event&);
			void update(float);

			void quit();
			bool isRunning();

			void deleteEntity(Entity*);

		private:
			SDL_Window* window;
			SDL_GLContext glcontext;

			bool run;

			void initGL(int, int);

			// tmp test ptrs
			std::list<Entity*> entities;
			std::list<Component*> components;
			std::vector<Collision*> collision_components;

			Entity* player;
			
			bool input_w = false, input_s = false, input_a = false, input_d = false;

			// collision functions
			void transformToEntity(Shape*, Entity*, int);

			void calculateAxis(float*, float*, float, float, float, float); // &ax, &ay, v1x, v1y, v2x, v2y
			void calculateProjection(float*, float*, float, float, float, float); // &px, &py, v1x, v1y, v2x, v2y
			float calculateScalar(float, float, float, float); // v1x, v1y, v2x, v2y

			float findMin(float, float, float, float);
			float findMax(float, float, float, float);


	};
}

#endif
