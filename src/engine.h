#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>

#include "entity.h"
#include "component.h"
#include "position.h"
#include "shape.h"
#include "velocity.h"

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

		private:
			SDL_Window* window;
			SDL_GLContext glcontext;

			bool run;

			void initGL(int, int);


			// tmp test ptrs
			Entity e;
			Shape* s;
			Velocity* v;
			Position* p;
	};
}

#endif
