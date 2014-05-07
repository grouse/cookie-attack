#ifndef DAMAGE_H
#define DAMAGE_H

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Damage : public Component {
		public:
			Damage(float);
			virtual ~Damage();

			virtual bool canAttach(Entity&);

			float damage;
	};
}

#endif
