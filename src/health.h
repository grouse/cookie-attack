#ifndef HEALTH_H
#define HEALTH_H

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Health : public Component {
		public:
			Health(float);
			virtual ~Health();

			virtual bool canAttach(Entity&);
			
			float health;
	};
}

#endif
