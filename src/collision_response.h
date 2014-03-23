#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

#include "entity.h"

namespace JEngine {

	class CollisionResponse {
		public:
			CollisionResponse() {}
			virtual ~CollisionResponse() {}

			virtual void execute(Entity&, Entity&) = 0;
	};
}

#endif
