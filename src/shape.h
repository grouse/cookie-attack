#ifndef SHAPE_H
#define SHAPE_H

#include <initializer_list>
#include <vector>

#include <SDL2/SDL_opengl.h>

#include "component.h"
#include "entity.h"

namespace JEngine {

	class Shape : public Component {
		public:
			Shape(std::initializer_list<GLfloat>);
			virtual ~Shape();

			virtual bool canAttach(Entity&);

			void rotate(float);
			void rotate(float, float, float, float);

			std::vector<GLfloat> vertices;
	};
}

#endif
