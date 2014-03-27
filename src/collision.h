#ifndef COLLISION_H
#define COLLISION_H

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Collision : public Component {
		public:
			Collision(void (*response)(Entity*, Entity*));
			virtual ~Collision();

			virtual bool canAttach(Entity&);
			void (*response)(Entity*, Entity*);
	};
}

#endif
