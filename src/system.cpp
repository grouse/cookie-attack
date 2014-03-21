#include "system.h"

#include <iostream>

namespace JEngine {

	System::System(GameObjects* objects) {
		this->objects = objects;
	}

	System::~System() {
		for (auto it = objects->entities.begin(); it != objects->entities.end(); it++)
			delete (*it);

		for (unsigned int i = 0; i < Component::NUM_TYPES; i++) 
			for (auto it = objects->components[i].begin(); it != objects->components[i].end(); it++)
				delete (*it);
	}


	void System::update(float dt) {}

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
	
	void System::deleteEntity(Entity* e) {
		for (unsigned int i = 0; i < Component::NUM_TYPES; i++) {
			if (e->components[i] != 0) {
				objects->components[i].remove(e->components[i]);
				
				delete e->components[i];
				e->components[i] = 0;
			}
		}

		objects->entities.remove(e);
		
		delete e;
		e = 0;
	}
}
