#ifndef COLLISION_H
#define COLLISION_H

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Collision : public Component {
		public:
			Collision(unsigned int);
			virtual ~Collision();

			virtual bool canAttach(Entity&);

			static const unsigned int
				EXPLOSIVE = 0,
				RIGID_BODY = 1;

			const unsigned int collision_type;
	};
}

#endif
