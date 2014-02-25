#include "velocity.h"

namespace JEngine {

	Velocity::Velocity(float x, float y, float z) : Component(Component::VELOCITY) {
		this->x = x;
		this->y = y;
		this->z = z;

		rotation = 0;
	}

	Velocity::~Velocity() {}

	bool Velocity::canAttach(Entity& e) {
		return true;
	}

	void Velocity::rotate(float angle) {
		float c = cos(angle);
		float s = sin(angle);

		float nx = x * c - y * s;
		float ny = x * s + y * c;
		
		this->x = nx;
		this->y = ny;

		rotation += angle;
	}

	void Velocity::setRotation(float angle) {
		if (rotation != 0)
			rotate(-rotation);

		rotate(angle);
	}
}
