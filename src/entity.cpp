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

	bool Entity::attach(Component* c) {
		if (components[c->type] == 0 && c->canAttach(*this)) {
			components[c->type] = c;
			c->owner = this;

			return true;
		}

		return false;
	}

	void Entity::detach(unsigned int c) {
		components[c]->owner = 0;
		components[c] = 0;
	}

	bool Entity::hasComponent(unsigned int c) {
		return (components[c] != 0);
	}

	Component* Entity::getComponent(unsigned int c) {
		return components[c];
	}
}
