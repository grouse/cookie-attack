#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "entity.h"
#include "component.h"

namespace JEngine {
	class System {
		public:
			System(unsigned int t);
			virtual ~System();

			const unsigned int type;
			static const unsigned int
				RENDER = 0,
				COLLISION = 1,
				NUM_TYPES = 2

			virtual void update(float) = 0;

			int pushEntity(Entity*);
			int attachComponent(int, Component*);
		protected:
			static std::vector<Component*> components[Component::NUM_TYPES];
			static std::vector<Entity*> entities;

	};
}

#endif
