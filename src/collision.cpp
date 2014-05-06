#include "collision.h"

#include <iostream>

namespace JEngine {
	Collision::Collision(void (*response)(Entity*, Entity*, GameObjects*)) : Component(Component::COLLISION)	{
		this->response = response;
	}

	Collision::~Collision() {}

	bool Collision::canAttach(Entity& e) {
		return true;
	}


	namespace CollisionResponse {
		void rigid_body(Entity* e1, Entity* e2, GameObjects* objects) {
			//std::cout << "test\n";
		}

		void projectile(Entity* e1, Entity* e2, GameObjects* objects) {
			objects->trashEntity(e1);
			std::cout << "test\n";
		}
	}
}
