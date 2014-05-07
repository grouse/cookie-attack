#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

#include "system.h"
#include "component.h"
#include "entity.h"
#include "health.h"
#include "game_objects.h"

namespace JEngine {
	class HealthSystem : public System {
		public:
			HealthSystem(GameObjects*);
			virtual ~HealthSystem();

			virtual void update(float dt);
	};
}

#endif
