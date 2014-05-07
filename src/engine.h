#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <iostream>
#include <list>
#include <vector>

#include "entity.h"
#include "component.h"

#include "system.h"
#include "movement_system.h"
#include "collision_system.h"
#include "render_system.h"
#include "life_time_system.h"
#include "health_system.h"

#include "shape.h"
#include "velocity.h"
#include "direction.h"
#include "collision.h"
#include "life_time.h"
#include "texture.h"
#include "health.h"
#include "damage.h"

#include "game_objects.h"

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

			GameObjects* objects;
			System* system;
			std::list<System*> systems;

			Entity* player;
			
			bool input_w = false, input_s = false, input_a = false, input_d = false;



	};
}

#endif
