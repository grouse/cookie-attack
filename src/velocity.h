#ifndef VELOCITY_H
#define VELOCITY_H

#include <math.h>

#include "entity.h"
#include "component.h"

namespace JEngine {

	class Velocity : public Component {
		public:
			Velocity(float, float, float);
			~Velocity();

			float x, y, z;
		
			virtual bool canAttach(Entity&);

			void rotate(float);
			void setRotation(float);
	
			float rotation;
	};
}

#endif
