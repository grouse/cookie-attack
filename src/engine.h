#include <SDL2/SDL.h>
#include <iostream>


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

		bool quit;
};
