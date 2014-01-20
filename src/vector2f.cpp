#include "vector2f.h"

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::~Vector2f() {}

float Vector2f::angleBetween(Vector2f other) {
	float dx = x - other.x;
	float dy = y - other.y;

	return atan(dy/dx);
}

float Vector2f::getMagnitude() {
	return sqrt(x*x + y*y);
}

void Vector2f::setRotation(float angle) {
	x = cos(angle);
	y = sin(angle);
}
