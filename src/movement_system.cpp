#include "movement_system.h"

namespace JEngine {

	MovementSystem::MovementSystem(GameObjects* objects) : System(objects) {}
	MovementSystem::~MovementSystem() {}

	void MovementSystem::update(float dt) {
		for (auto it = objects->components[Component::VELOCITY].begin(); it != objects->components[Component::VELOCITY].end(); it++) {

			Velocity* v = (Velocity*) (*it);
			Entity* e = v->owner;;


			
			//Direction* d = (Direction*) e->components[Component::DIRECTION];

			e->pos += v->vec3 * dt;

			//e->x += v->x*dt;
			//e->y += v->y*dt;
			//v->z += v->z*dt;
		}
	}
}
