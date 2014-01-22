#include <SDL2/SDL.h>

#include "engine.h"

int main(int argc, char* argv[]) {
	JEngine::Engine engine;

	if (engine.init("Cookie Attack!", 1280, 720) != 0)
		return -1;

	Uint32 old_time, current_time;
	current_time = SDL_GetTicks();

	float dt;

	while (engine.isRunning()) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			engine.handleInput(e);

		old_time = current_time;
		current_time = SDL_GetTicks();
		dt = (current_time - old_time) / 1000.0f;

		engine.update(dt);		
	}
	
	return 0;
}
