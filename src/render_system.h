#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL_opengl.h>

#include <SDL2/SDL.h>

#include "system.h"
#include "entity.h"
#include "component.h"
#include "shape.h"
#include "texture.h"

namespace JEngine {
	class RenderSystem : public System {
		public:
			RenderSystem(GameObjects*, SDL_Window*);
			virtual ~RenderSystem();

			virtual void update(float);

			

		private:
			SDL_Window* window;

			float uv[8];
	};
}

#endif
