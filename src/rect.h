#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL_opengl.h>

class Rect {
	public:
		Rect(float, float, float, float);
		virtual ~Rect();

		void render();
		void move(float, float);

	private:
		float x, y;
		float w, h;


};

#endif
