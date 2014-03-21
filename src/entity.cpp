#include "entity.h"

namespace JEngine {
	Entity::Entity(float x, float y, float z) {
		for (int i = 0; i < Component::NUM_TYPES; i++) 
			components[i] = 0;

		this->x = x;
		this->y = y;
		this->z = z;
	}

	Entity::~Entity() {}

	int Entity::attach(unsigned int type, Component* c) {
		if (components[type] != 0)
			return -1;
		
		components[type] = c;
		return 0;	
	}
}
