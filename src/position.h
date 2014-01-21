#ifndef POSITION_H
#define POSITION_H

#include "component.h"
#include "entity.h"

namespace JEngine {

	class Position : public Component {
		public:
			Position(float, float, float);
			virtual ~Position();

			virtual bool canAttach(Entity&);

			float x, y, z;
	};
}

#endif
