#include "collision.h"

namespace JEngine {
	Collision::Collision() : Component(Component::COLLISION) {

	}

	Collision::~Collision() {}

	bool Collision::canAttach(Entity& e) {
		return true;
	}

}
