#ifndef COLLISION_H
#define COLLISION_H

#include "entity.h"
#include "component.h"

#include "game_objects.h"

namespace JEngine {
	class CollisionSystem;

	class Collision : public Component {
		public:
			Collision(void (*response)(Entity*, Entity*, GameObjects*));
			virtual ~Collision();

			virtual bool canAttach(Entity&);
			void (*response)(Entity*, Entity*, GameObjects*);
	};

	namespace CollisionResponse {
		void rigid_body(Entity*, Entity*, GameObjects*);
		void projectile(Entity*, Entity*, GameObjects*);

	}
}

#endif
