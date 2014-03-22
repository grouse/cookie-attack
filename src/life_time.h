#ifndef LIFE_TIME_H
#define LIFE_TIME_H

#include "entity.h"
#include "component.h"

namespace JEngine {

	class LifeTime : public Component {
		public:
			LifeTime(float);
			virtual ~LifeTime();

			virtual bool canAttach(Entity&);

			float remaining;
	};
}

#endif
