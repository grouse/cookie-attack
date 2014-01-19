#include "vector2f.h"

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::~Vector2f() {}

void Vector2f::normalize() {
	float magnitude = getMagnitude();
	
	if (magnitude > 0.0) {
		x = x / magnitude;
		y = y / magnitude;
	}
}

float Vector2f::angleBetween(Vector2f other) {
	float dx = x - other.x;
	float dy = y - other.y;

	return atan(dy/dx);

	/** return acos(
		(other.x * x + other.y * y) / 
		(other.getMagnitude() * getMagnitude())
	); **/
}

float Vector2f::getMagnitude() {
	return sqrt(x*x + y*y);
}

void Vector2f::rotate(float angle) {
	Vector2f other(cos(angle), sin(angle));
	float nx = x * other.x - y * other.y;
	float ny = x * other.x + y * other.y;

	x = nx;
	y = nx;
}

void Vector2f::setRotation(float angle) {
	x = cos(angle);
	y = sin(angle);
}
