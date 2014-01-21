#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <math.h>

#include "rect.h"

namespace JEngine {
	class Engine {
		public:
			Engine();
			virtual ~Engine();

			int init();
			void run();
			void cleanup();
			void exit();

		private:
			SDL_Window* window;
			SDL_GLContext glcontext;

			bool quit;

			void initGL(int, int);

			Rect* frame[4];
			Rect* player1;
			Rect* player2;
			Rect* ball;
	};
}

#endif
