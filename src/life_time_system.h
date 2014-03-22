#ifndef LIFE_TIME_SYSTEM_H
#define LIFE_TIME_SYSTEM_H

#include <list>

#include "system.h"
#include "entity.h"
#include "component.h"
#include "life_time.h"

namespace JEngine {
	class LifeTimeSystem : public System {
		public:
			LifeTimeSystem(GameObjects*);
			virtual ~LifeTimeSystem();

			virtual void update(float);

	};
}

#endif
