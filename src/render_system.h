#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL2/SDL_opengl.h>

#include "system.h"
#include "entity.h"
#include "component.h"
#include "shape.h"

namespace JEngine {
	class RenderSystem : public System {
		public:
			RenderSystem();
			virtual ~RenderSystem();

			virtual void update(float);
	};
}

#endif
