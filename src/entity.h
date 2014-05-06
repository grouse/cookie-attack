#ifndef ENTITY_H
#define ENTITY_H

#include <glm/vec3.hpp>

#include "component.h"

namespace JEngine {
	
	class Entity {
		public:
			Entity(float, float, float);
			Entity(glm::vec3);

			~Entity();

			glm::vec3 pos;
	
			int attach(unsigned int, Component*);

			Component* components[Component::NUM_TYPES];
	};
}

#endif
