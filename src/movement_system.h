#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "system.h"
#include "entity.h"
#include "component.h"
#include "velocity.h"
#include "diretion.h"

namespace JEngine {

	class MovementSystem : public System {
		public:
			MovementSystem();
			~MovementSystem();

			virtual void update(float dt);
	};
}

#endif
