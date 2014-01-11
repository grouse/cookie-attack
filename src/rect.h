#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL_opengl.h>

class Rect {
	public:
		Rect(float, float, float, float, float);
		virtual ~Rect();

		enum DIRECTION { UP = -1, DOWN = 1, NONE = 0 };

		void render();
		void update();

		void move(DIRECTION, DIRECTION);
		void move(float, float);

		int intersects(Rect*);


	private:
		float x, y;
		float w, h;
		float speed;
		DIRECTION directionX, directionY;


};

#endif
