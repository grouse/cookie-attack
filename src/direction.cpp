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

	void Direction::rotate(double angle) {
		double c = cos(angle);
		double s = sin(angle);

		double nx = x * c - y * s;
		double ny = x * s + y * c;
		
		this->x = nx;
		this->y = ny;

		rotation += angle;
	}

	void Direction::setRotation(double angle) {
		rotate(-rotation);
		rotate(angle);
	}
}
