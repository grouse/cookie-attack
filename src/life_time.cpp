#include "life_time.h"

namespace JEngine {

	LifeTime::LifeTime(float t) : Component(Component::LIFETIME) {
		remaining = t;
	}

	LifeTime::~LifeTime() {}

	bool LifeTime::canAttach(Entity& e) {
		return true;
	}


}
