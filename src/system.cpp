#include "system.h"

namespace JEngine {

	System::System(unsigned int t) : type(t) {}
	System::~System() {
		for (auto it = entities.begin(); it < entities.end(); it++)
			delete (*it);

		for (unsigned int i = 0; i < Component::NUM_TYPES; i++) 
			for (auto it = components[i].begin(); it < components[i].end(); it++)
				delete (*it);
	}

	int System::pushEntity(Entity* e) {
		entities.push_back(e);
		return entities.size()-1;
	}

	int System::attachComponent(int e, Component* c) {
		if (c->canAttach(*entities[e]))
			return -1;

		components[c->type].push_back(c);
		
		entities[e]->attach(c->type, components[c->type].size()-1);
		c->owner = e;		
		
		return components[c->type].size()-1;
	}
}
