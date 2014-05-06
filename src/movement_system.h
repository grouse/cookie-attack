#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <glm/glm.hpp>

#include "system.h"
#include "entity.h"
#include "component.h"
#include "velocity.h"
#include "direction.h"

namespace JEngine {

	class MovementSystem : public System {
		public:
			MovementSystem(GameObjects*);
			~MovementSystem();

			virtual void update(float dt);
	};
}

#endif
