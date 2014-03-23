#ifndef NULL_RESPONSE_H
#define NULL_RESPONSE_H

#include "collision_response.h"
#include "entity.h"

namespace JEngine {
	class NullResponse : public CollisionResponse {
		public: 
			NullResponse() {}
			~NullResponse() {}

			virtual void execute(Entity& e1, Entity& e2) {}
	};
}

#endif
