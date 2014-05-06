#ifndef VELOCITY_H
#define VELOCITY_H

#include <math.h>

#include <glm/vec3.hpp>

#include "entity.h"
#include "component.h"

namespace JEngine {

	class Velocity : public Component {
		public:
			Velocity(float, float, float, float, float, float);
			virtual ~Velocity();

			glm::vec3 vec3;

			virtual bool canAttach(Entity&);

			float rotation;
			float acceleration, deacceleration, max_speed;

	};
}

#endif
