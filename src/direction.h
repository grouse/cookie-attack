#ifndef DIRECTION_H
#define DIRECTION_H

#include <math.h>

#include "entity.h"
#include "component.h"

namespace JEngine {

	class Direction : public Component {
		public:
			Direction(float, float, float);
			~Direction();

			float x, y, z;
		
			virtual bool canAttach(Entity&);

			void rotate(float);
			void setRotation(float);
	
			float rotation;
	};
}

#endif
