#include "collision.h"

#include <iostream>

namespace JEngine {
	Collision::Collision(void (*response)(Entity*, Entity*, glm::vec3, GameObjects*)) : Component(Component::COLLISION)	{
		this->response = response;
	}

	Collision::~Collision() {}

	bool Collision::canAttach(Entity& e) {
		return true;
	}


	namespace CollisionResponse {
		void rigid_body(Entity* e1, Entity* e2, glm::vec3 overlap, GameObjects* objects) {
			e1->pos -= overlap;
			
			Velocity* v = (Velocity*) e1->components[Component::VELOCITY];
			v->vec3 = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		
		void static_body(Entity* e1, Entity* e2, glm::vec3 overlap, GameObjects* objects) {}

		void projectile(Entity* e1, Entity* e2, glm::vec3 overlap, GameObjects* objects) {
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
