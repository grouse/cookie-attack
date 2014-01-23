#ifndef ENTITY_H
#define ENTITY_H

#include "component.h"

namespace JEngine {
	
	class Entity {
		public:
			Entity();
			~Entity();

			bool hasComponent(unsigned int);
			Component* getComponent(unsigned int);
			
			bool attach(Component*);
			void detach(unsigned int);

		private:
			Component* components[Component::NUM_TYPES];
	
	};
}

#endif
