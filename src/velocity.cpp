#include "velocity.h"

#include <iostream>

namespace JEngine {

	Velocity::Velocity(float x, float y, float z, float acceleration, float deacceleration, float max_speed) : Component(Component::VELOCITY), vec3(x, y, z) {

		this->acceleration = acceleration;
		this->deacceleration = deacceleration;
		this->max_speed = max_speed;

		rotation = 0;
	}

	Velocity::~Velocity() {}

	bool Velocity::canAttach(Entity& e) {
		return true;
	}
}
