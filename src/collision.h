#ifndef COLLISION_H
#define COLLISION_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "entity.h"
#include "component.h"

#include "game_objects.h"

#include "damage.h"
#include "health.h"
#include "velocity.h"

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
