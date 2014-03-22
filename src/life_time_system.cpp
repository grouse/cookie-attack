#include "life_time_system.h"

namespace JEngine {

	LifeTimeSystem::LifeTimeSystem(GameObjects* objects) : System(objects) {}
	LifeTimeSystem::~LifeTimeSystem() {}

	void LifeTimeSystem::update(float dt) {
		std::list<LifeTime*> removal;
		
		for (auto it = objects->components[Component::LIFETIME].begin(); it != objects->components[Component::LIFETIME].end(); it++) {
			LifeTime* c = (LifeTime*) (*it);

			c->remaining -= dt;
			if (c->remaining <= 0)
				removal.push_back(c);
		}

		for (auto it = removal.begin(); it != removal.end(); it++) 
			deleteEntity((*it)->owner);
	}

}
