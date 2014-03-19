#include "collision.h"

namespace JEngine {
	Collision::Collision(unsigned int t) : 
		Component(Component::COLLISION),
   		collision_type(t)	{}

	Collision::~Collision() {}

	bool Collision::canAttach(Entity& e) {
		return true;
	}

}
