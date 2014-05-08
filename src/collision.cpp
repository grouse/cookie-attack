#include "collision.h"

#include <iostream>

namespace JEngine {
	Collision::Collision(void (*response)(Entity*, Entity*, glm::vec2, GameObjects*)) : Component(Component::COLLISION)	{
		this->response = response;
	}

	Collision::~Collision() {}

	bool Collision::canAttach(Entity& e) {
		return true;
	}


	namespace CollisionResponse {
		void rigid_body(Entity* e1, Entity* e2, glm::vec2 overlap, GameObjects* objects) {
			//std::cout << "test\n";
			std::cout << "overlap: (" << overlap.x << ", " << overlap.y << ")\n";
		}

		void projectile(Entity* e1, Entity* e2, glm::vec2 overlap, GameObjects* objects) {
			if (e1->components[Component::DAMAGE] != 0 && e2->components[Component::HEALTH] != 0) {
				Damage* d = (Damage*) e1->components[Component::DAMAGE];
				Health* h = (Health*) e2->components[Component::HEALTH];

				h->health -= d->damage;
				std::cout << "DAMAGE! " << d->damage << "\nRemaining health: " << h->health << "\n";
			}

			objects->trashEntity(e1);
		}
	}
}
