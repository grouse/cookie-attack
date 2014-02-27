#include "direction.h"

namespace JEngine {

	Direction::Direction(float x, float y, float z) : Component(Component::DIRECTION) {
		this->x = x;
		this->y = y;
		this->z = z;

		rotation = 0;
	}

	Direction::~Direction() {}

	bool Direction::canAttach(Entity& e) {
		return true;
	}

	void Direction::rotate(float angle) {
		float c = cos(angle);
		float s = sin(angle);

		float nx = x * c - y * s;
		float ny = x * s + y * c;
		
		this->x = nx;
		this->y = ny;

		rotation += angle;
	}

	void Direction::setRotation(float angle) {
		rotate(-rotation);
		rotate(angle);
	}
}
