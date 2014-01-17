#ifndef VECTOR2F_H
#define VECTOR2F_H


#include <math.h>

class Vector2f {
	public:
		Vector2f(float, float);
		~Vector2f();
		
		float x, y;

		void normalize();
};

#endif // VECTOR2F_H
