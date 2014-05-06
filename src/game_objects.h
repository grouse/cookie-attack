#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include <list>

#include "entity.h"
#include "component.h"

namespace JEngine {
	class GameObjects {

		public: 
			GameObjects();
			~GameObjects();

			std::list<Component*> components[Component::NUM_TYPES];
			std::list<Entity*> entities;

			void trashEntity(Entity*);
			void processTrash();

		private:
			std::list<Entity*> trash;
	};
}

#endif
