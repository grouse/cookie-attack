#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <list>

#include <glm/glm.hpp>

#include "system.h"
#include "entity.h"
#include "component.h"
#include "collision.h"
#include "shape.h"
#include "game_objects.h"

namespace JEngine {
	class CollisionSystem : public System {
		public:
			CollisionSystem(GameObjects*);
			virtual ~CollisionSystem();

			virtual void update(float dt);

		private:
			// collision functions
			bool overlaps(glm::vec3, glm::vec3);
			float getOverlap(glm::vec3, glm::vec3);

			bool contains(float, glm::vec3);
			glm::vec3 project(glm::vec3*, glm::vec3);
			glm::vec3 perp(glm::vec3);
	};
}

#endif
