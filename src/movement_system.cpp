#include "movement_system.h"

namespace JEngine {

	MovementSystem::MovementSystem(GameObjects* objects) : System(objects) {}
	MovementSystem::~MovementSystem() {}

	void MovementSystem::update(float dt) {
		for (auto it = objects->components[Component::VELOCITY].begin(); it != objects->components[Component::VELOCITY].end(); it++) {

			Velocity* v = (Velocity*) (*it);
			Entity* e = objects->entities[v->owner];

			int direction = e->getComponent(Component::DIRECTION);

			if (direction != -1) {
				Direction* d = (Direction*) (objects->components[Component::DIRECTION][direction]);

				e->x += v->x*d->x*dt;
				e->y += v->y*d->y*dt;
				e->z += v->z*d->z*dt;

			} else {
				e->x += v->x*dt;
				e->y += v->y*dt;
				v->z += v->z*dt;
			}
		}
	}
}
