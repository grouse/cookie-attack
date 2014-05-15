#ifndef COLLISION_H
#define COLLISION_H

#include <glm/vec2.hpp>

#include "entity.h"
#include "component.h"

#include "game_objects.h"

#include "damage.h"
#include "health.h"

namespace JEngine {
	class CollisionSystem;

	class Collision : public Component {
		public:
			Collision(void (*response)(Entity*, Entity*, glm::vec3, GameObjects*));
			virtual ~Collision();

			virtual bool canAttach(Entity&);
			void (*response)(Entity*, Entity*, glm::vec3, GameObjects*);
	};

	namespace CollisionResponse {
		void rigid_body(Entity*, Entity*, glm::vec3,  GameObjects*);
		void static_body(Entity*, Entity*, glm::vec3,  GameObjects*);
		void projectile(Entity*, Entity*, glm::vec3, GameObjects*);

	}
}

#endif
