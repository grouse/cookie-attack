#include "rect.h"

#include <iostream>

Rect::Rect(float x, float y, float w, float h, float speed) : 
	size(w, h),
	pos(x, y),
	origin(x + w/2, y + h/2) {
	
	this->speed = speed;
}

Rect::Rect(float x, float y, float w, float h) : 
	size(w, h),
	pos(x, y),
	origin(x + w/2, y + h/2) {
	
	this->speed = 0;
}

Rect::~Rect() {}

int Rect::isIntersecting(Rect* r) {

	if (pos.y+size.y < r->pos.y) return 0;
	if (pos.y > r->pos.y+r->size.y) return 0;
	if (pos.x+size.x < r->pos.x) return 0;
	if (pos.x > r->pos.x+r->size.x) return 0;
	
	return 1;
}

Vector2f Rect::getOrigin() {
	Vector2f origin(pos.x + size.x/2, pos.y + size.y/2);

	//return Vector2f(pos.x + size.x/2, pos.y + size.y/2);
	return origin;
}


Vector2f Rect::getIntersection(Rect* r) {

	float ix = 0, iy = 0;


	if (!(pos.x > r->pos.x && pos.x + size.x < r->pos.x + r->size.x)) {
		if (pos.x > r->pos.x) {
			ix = r->pos.x + r->size.x - pos.x;
		} else if (pos.x < r->pos.x) {
			ix = pos.x + size.x - r->pos.x;
		}
	}
	
	if (!(pos.y > r->pos.y && pos.y + size.y < r->pos.y + r->size.y)) {
		if (pos.y >= r->pos.y) {
			iy = r->pos.y + r->size.y - pos.y;
		} else {
			iy = r->pos.y - pos.y - size.y;
		}
	} 

	return Vector2f(ix, iy);
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

void Rect::setPos(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Rect::move(float dx, float dy) {
	pos.x += dx;
	pos.y += dy;
}

void Rect::move(Vector2f& dxdy) {
	pos.x += dxdy.x;
	pos.y += dxdy.y;
}
