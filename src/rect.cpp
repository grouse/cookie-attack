#include "rect.h"

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::~Rect() {

}

void Rect::render() { 
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glColor3f(255, 255, 255);

	glBegin(GL_QUADS);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
	   	glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();	
}

void Rect::move(float dx, float dy) {
	x += dx;
	y += dy;
}
