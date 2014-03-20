#include "system.h"

#include <iostream>

namespace JEngine {

	System::System(GameObjects* objects) {
		this->objects = objects;
	}

	System::~System() {
		for (auto it = objects->entities.begin(); it < objects->entities.end(); it++)
			delete (*it);

		for (unsigned int i = 0; i < Component::NUM_TYPES; i++) 
			for (auto it = objects->components[i].begin(); it < objects->components[i].end(); it++)
				delete (*it);
	}


	void System::update(float dt) {}

	int System::pushEntity(Entity* e) {
		objects->entities.push_back(e);
		return objects->entities.size()-1;
	}

	int System::attachComponent(int e, Component* c) {
		if (!c->canAttach(*objects->entities[e])) {
			std::cout << "Failed to attach component: " << c->type << " to entity: " << e << "\n";
			return -1;
		}

		objects->components[c->type].push_back(c);
		
		objects->entities[e]->attach(c->type, objects->components[c->type].size()-1);
		c->owner = e;		
		
		return objects->components[c->type].size()-1;
	}

	Entity* System::getEntity(int e) {
		return objects->entities[e];
	}

	Component* System::getComponent(unsigned int t, int c) {
		return objects->components[t][c];
	}
}
