#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <vector>

#include "entity.h"
#include "component.h"

namespace JEngine {
	class GameObjects {

		public: 
			GameObjects() {}
			~GameObjects() {}

			std::vector<Component*> components[Component::NUM_TYPES];
			std::vector<Entity*> entities;
	};
}

#endif
