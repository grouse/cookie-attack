#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H

#include "collision_response.h"
#include "entity.h"

namespace JEngine {
	class Explosive : public CollisionResponse {
		public:
			Explosive(float);
			virtual ~Explosive();

			virtual void execute(Entity&, Entity&);

		private:
			float damage;
	};
}

#endif
