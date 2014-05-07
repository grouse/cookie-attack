#include "health.h"

namespace JEngine {

	Health::Health(float hp) : Component(Component::HEALTH) {
		this->health = hp;
	}

	Health::~Health() {}

	bool Health::canAttach(Entity& e) {
		return true;
	}

}
