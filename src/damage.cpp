#include "damage.h"

namespace JEngine {
	
	Damage::Damage(float dmg) : Component(Component::DAMAGE) {
		this->damage = dmg;
	}

	Damage::~Damage() {}

	bool Damage::canAttach(Entity& e) {
		return true;
	}

}
