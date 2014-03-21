#include "shape.h"

#include <math.h>
#include <iostream>

namespace JEngine {
	
	Shape::Shape(std::initializer_list<GLfloat> v) : 
		Component(Component::SHAPE),
  		vertices(v)	{
		
			rotation = 0;
	}

	Shape::~Shape() {}

	bool Shape::canAttach(Entity& e) {
		return true;
	}

	void Shape::rotate(double angle) {
		double s = sin(angle); // computer sin & cos once
		double c = cos(angle);

		double xt, yt; // transformed to ox, oy origin
		double xr, yr; // rotated coordinates

		xt = vertices[0];
		yt = vertices[1];

		xr = xt * c - yt * s;
		yr = xt * s + yt * c;

		vertices[0] = xr;
		vertices[1] = yr;

		
		xt = vertices[3];
		yt = vertices[4];

		xr = xt * c - yt * s;
		yr = xt * s + yt * c;

		vertices[3] = xr;
		vertices[4] = yr;

		xt = vertices[6];
		yt = vertices[7];

		xr = xt * c - yt * s;
		yr = xt * s + yt * c;

		vertices[6] = xr;
		vertices[7] = yr;

		xt = vertices[9];
		yt = vertices[10];

		xr = xt * c - yt * s;
		yr = xt * s + yt * c;

		vertices[9] = xr;
		vertices[10] = yr;

		rotation += angle;
	}

	void Shape::setRotation(double angle) {
		if (rotation != 0)
			rotate(-rotation);

		rotate(angle);
	}
}
