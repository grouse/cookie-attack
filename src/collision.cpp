#include "collision.h"

namespace JEngine {
	Collision::Collision(void (*response)(Entity*, Entity*)) : Component(Component::COLLISION)	{
		this->response = response;
	}

	Collision::~Collision() {}

	bool Collision::canAttach(Entity& e) {
		return true;
	}

}
