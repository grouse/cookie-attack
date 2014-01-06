#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <math.h>

#include "rect.h"

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
		SDL_Renderer* renderer;
		SDL_GLContext glcontext;

		bool quit;

		void initGL(int, int);

	public:
		Rect** frame;

};

#endif
