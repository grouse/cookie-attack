#include "shape.h"

#include <math.h>

namespace JEngine {
	
	Shape::Shape(std::initializer_list<GLfloat> v) : 
		vertices(v),
		Component(Component::SHAPE) {
	}

	Shape::~Shape() {}

	bool Shape::canAttach(Entity& e) {
		return true;
	}

	void Shape::rotate(float angle) {
		GLfloat x = vertices[0] * cos(angle) - vertices[1] * sin(angle); 
		GLfloat y = vertices[0] * cos(angle) + vertices[1] * sin(angle);

		vertices[0] = x;
		vertices[1] = y;

			
		x = vertices[3] * cos(angle) - vertices[4] * sin(angle); 
		y = vertices[3] * cos(angle) + vertices[4] * sin(angle);

		vertices[3] = x;
		vertices[4] = y;

		x = vertices[6] * cos(angle) - vertices[7] * sin(angle); 
		y = vertices[6] * cos(angle) + vertices[7] * sin(angle);

		vertices[6] = x;
		vertices[7] = y;

		x = vertices[9] * cos(angle) - vertices[10] * sin(angle); 
		y = vertices[9] * cos(angle) + vertices[10] * sin(angle);

		vertices[9] = x;
		vertices[10] = y;
	}
}
