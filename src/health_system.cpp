#include "health_system.h"

#include <iostream>

namespace JEngine {
	HealthSystem::HealthSystem(GameObjects* objects) : System(objects) {}
	HealthSystem::~HealthSystem() {}

	void HealthSystem::update(float dt) {
		for (auto it = objects->components[Component::HEALTH].begin(); it != objects->components[Component::HEALTH].end(); it++) {
			Health* h = (Health*) (*it);
			
			if (h->health <= 0) 
				objects->trashEntity(h->owner);
			
		}	
	}
}
