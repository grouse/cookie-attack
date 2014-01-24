#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <list>

#include "entity.h"
#include "component.h"
#include "position.h"
#include "velocity.h"
#include "shape.h"


namespace JEngine {
	class ComponentManager {
		public: 
			ComponentManager();
			~ComponentManager();

			void addComponent(Component*);
			std::list<Component*> getComponents(unsigned int);

		private:
			std::list<Component*> components;

	};
}

#endif
