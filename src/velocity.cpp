#include "velocity.h"

namespace JEngine {

	Velocity::Velocity(float x, float y, float z, float acceleration, float deacceleration, float max_speed) : Component(Component::VELOCITY) {
		this->x = x;
		this->y = y;
		this->z = z;

		this->acceleration = acceleration;
		this->deacceleration = deacceleration;
		this->max_speed = max_speed;

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
		rotate(-rotation);
		rotate(angle);
	}
}
