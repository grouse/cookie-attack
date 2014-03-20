#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "entity.h"
#include "component.h"
#include "game_objects.h"

namespace JEngine {
	class System {
		public:
			System(GameObjects*);
			virtual ~System();

			virtual void update(float);

			int pushEntity(Entity*);
			int attachComponent(int, Component*);

			Entity* getEntity(int);
			Component* getComponent(unsigned int, int);

			void deleteEntity(int);

		protected:
			GameObjects* objects;

	};
}

#endif
