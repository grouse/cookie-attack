#include "velocity.h"

namespace JEngine {

	Velocity::Velocity(float x, float y, float z) : Component(Component::VELOCITY) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Velocity::~Velocity() {}

	bool Velocity::canAttach(Entity& e) {
		return true;
	}

	void Velocity::rotate(float angle) {
	}
}
