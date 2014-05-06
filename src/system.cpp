#include "system.h"

#include <iostream>

namespace JEngine {

	System::System(GameObjects* objects) {
		this->objects = objects;
	}

	System::~System() {}


	void System::update(float dt) {
		objects->processTrash();
	}

	Entity* System::pushEntity(Entity* e) {
		objects->entities.push_back(e);
		return e;
	}

	Component* System::attachComponent(Entity* e, Component* c) {
		if (!c->canAttach(*e)) {
			std::cout << "Failed to attach component: " << c->type << " to entity: " << e << "\n";
			return 0;
		}

		objects->components[c->type].push_back(c);
	
		e->attach(c->type, c);
		c->owner = e;		
		
		return c;
	}
}
