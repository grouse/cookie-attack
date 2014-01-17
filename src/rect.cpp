#include "rect.h"

#include <iostream>

Rect::Rect(float x, float y, float w, float h, float speed) : 
	size(w, h),
	pos(x, y) {
	
	this->speed = speed;
}

Rect::Rect(float x, float y, float w, float h) : 
	size(w, h),
	pos(x, y) {
	
	this->speed = 0;
}

Rect::~Rect() {}

int Rect::intersects(Rect* r) {

	if (pos.y+size.y < r->pos.y) return 0;
	if (pos.y > r->pos.y+r->size.y) return 0;
	if (pos.x+size.x < r->pos.x) return 0;
	if (pos.x > r->pos.x+r->size.x) return 0;

	return 1;
}

void Rect::render() { 
	glTranslatef(pos.x, pos.y, 0.0f);

	glColor3f(255, 255, 255);

	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0.0f);
		glVertex3f(size.x, 0, 0.0f);
	   	glVertex3f(size.x, size.y, 0.0f);
		glVertex3f(0, size.y, 0.0f);
	glEnd();

	glTranslatef(-pos.x, -pos.y, 0.0f);	
}

void Rect::update(float dt) {
	if (direction == NULL) 
		return;

	pos.x += dt*direction->x*speed;
	pos.y += dt*direction->y*speed;
}

void Rect::setDirection(Vector2f* direction) {
	this->direction = direction;
}

void Rect::move(float dx, float dy) {
	pos.x += dx;
	pos.y += dy;
}

void Rect::move(Vector2f& dxdy) {
	pos.x += dxdy.x;
	pos.y += dxdy.y;
}
