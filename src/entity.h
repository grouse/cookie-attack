#ifndef ENTITY_H
#define ENTITY_H

#include "component.h"

namespace JEngine {
	
	class Entity {
		public:
			Entity(float, float, float);
			~Entity();

			float x, y, z;
	
			int attach(unsigned int, int);
			void detach(unsigned int);

			int getComponent(unsigned int);

		private:	
			int components[Component::NUM_TYPES];
	};
}

#endif
