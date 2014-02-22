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
		float nx = x * cos(angle) - y * sin(angle);
		float ny = x * sin(angle) + y * cos(angle);
		
		this->x = nx;
		this->y = ny;
	}
}
