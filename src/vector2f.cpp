#include "vector2f.h"


Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::~Vector2f() {}

void Vector2f::normalize() {
	float magnitude = sqrt(x*x + y*y);
	
	if (magnitude > 0.0) {
		x = x / magnitude;
		y = y / magnitude;
	}
}
