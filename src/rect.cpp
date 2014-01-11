#include "rect.h"

#include <iostream>


Rect::Rect(float x, float y, float w, float h, float speed) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;
	directionX = NONE;
	directionY = NONE;
}

Rect::~Rect() {

}

int Rect::intersects(Rect* r) {

	if (y+h < r->y) return 0;
	if (y > r->y+r->h) return 0;
	if (x+w < r->x) return 0;
	if (x > r->x+r->w) return 0;

	return 1;
}

void Rect::render() { 
	glTranslatef(x, y, 0.0f);

	glColor3f(255, 255, 255);

	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0.0f);
		glVertex3f(w, 0, 0.0f);
	   	glVertex3f(w, h, 0.0f);
		glVertex3f(0, h, 0.0f);
	glEnd();

	glTranslatef(-x, -y, 0.0f);	
}

void Rect::update() {
	x += speed*directionX;
	y += speed*directionY;
}

void Rect::move(DIRECTION x, DIRECTION y) {
	directionX = x;
	directionY = y;
}

void Rect::move(float dx, float dy) {
	x += dx;
	y += dy;
}
