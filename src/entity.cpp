#include "entity.h"

namespace JEngine {
	Entity::Entity(float x, float y, float z) {
		for (int i = 0; i < Component::NUM_TYPES; i++) 
			components[i] = -1;

		this->x = x;
		this->y = y;
		this->z = z;
	}

	Entity::~Entity() {}

	int Entity::attach(unsigned int c, int i) {
		if (components[c] != -1)
			return -1;

		components[c] = i; 
	}

	void Entity::detach(unsigned int c) {
		components[c] = -1;	
	}

	int Entity::getComponent(unsigned int c) {
		return components[c];
	}
}
