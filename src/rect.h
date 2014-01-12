#ifndef RECT_H
#define RECT_H

#include <math.h>

#include <SDL2/SDL_opengl.h>

#include "polar2f.h"

class Rect {
	public:
		Rect(float, float, float, float);
		virtual ~Rect();

		void render();
		void update();

		void move(Polar2f*);
		void move(float, float);

		int intersects(Rect*);

	private:
		float x, y;
		float w, h;
		Polar2f* target;
};

#endif
