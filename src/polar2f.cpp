#include "polar2f.h"

#include <iostream>

#define PI 3.14159265

Polar2f::Polar2f(float angle, float length) {
	this->angle = angle*PI;
	this->length = length;
}

Polar2f::~Polar2f() {

}

void Polar2f::rotate(float dangle) {
	this->angle += dangle*PI;
}

float Polar2f::getAngle() { 
	return angle;
}

float Polar2f::getLength() {
	return length;
}
