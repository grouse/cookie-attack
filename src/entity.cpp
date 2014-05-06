#include "entity.h"

namespace JEngine {
	Entity::Entity(glm::vec3 vec) : pos(vec) {
		for (unsigned int i = 0; i < Component::NUM_TYPES; i++) 
			components[i] = 0;
	}
	
	Entity::Entity(float x, float y, float z) : pos(x, y, z) {
		for (unsigned int i = 0; i < Component::NUM_TYPES; i++) 
			components[i] = 0;
	}

	Entity::~Entity() {}

	int Entity::attach(unsigned int type, Component* c) {
		if (components[type] != 0)
			return -1;
		
		components[type] = c;
		return 0;	
	}
}
