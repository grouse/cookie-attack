#ifndef RECT_H
#define RECT_H

#include <math.h>

#include <SDL2/SDL_opengl.h>

#include "vector2f.h"

class Rect {
	public:
		Rect(float, float, float, float, float);
		Rect(float, float, float, float);

		virtual ~Rect();

		void render();
		void update(float);

		void setDirection(Vector2f*);
		
		void move(float, float);
		void move(Vector2f&);
		
		Vector2f getIntersection(Rect*);
		int isIntersecting(Rect*);

		void setPos(float, float);

		Vector2f getOrigin();

	private:
		Vector2f pos, origin;
		Vector2f size;
		Vector2f* direction;

		float speed;
};

#endif
