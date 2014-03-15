#ifndef COLLISION_H
#define COLLISION_H

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Collision : public Component {
		public:
			Collision();
			virtual ~Collision();

			virtual bool canAttach(Entity&);
	};
}

#endif
