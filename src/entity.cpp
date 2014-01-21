#include "entity.h"

namespace JEngine {
	Entity::Entity() {
		for (int i = 0; i < Component::NUM_TYPES; i++) 
			components[i] = 0;
	}

	Entity::~Entity() {}

	bool Entity::attach(Component* c) {
		if (components[c->type] == 0 && c->canAttach(*this)) {
			components[c->type] = c;
			return true;
		}

		return false;
	}

	bool Entity::hasComponent(unsigned int c) {
		return (components[c] != 0);
	}
}
