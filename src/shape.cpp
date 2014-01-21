#include "shape.h"

namespace JEngine {
	
	Shape::Shape(std::initializer_list<GLfloat> v) : 
		vertices(v),
		Component(Component::SHAPE) {
	}

	Shape::~Shape() {}

	bool Shape::canAttach(Entity& e) {
		return (e.hasComponent(Component::POSITION));
	}
}
