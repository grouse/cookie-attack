#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

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
			void transformToEntity(Shape*, Entity*, int);

			void calculateAxis(float*, float*, float, float, float, float); // &ax, &ay, v1x, v1y, v2x, v2y
			void calculateProjection(float*, float*, float, float, float, float); // &px, &py, v1x, v1y, v2x, v2y
			float calculateScalar(float, float, float, float); // v1x, v1y, v2x, v2y

			float findMin(float, float, float, float);
			float findMax(float, float, float, float);
			
	};
}

#endif
