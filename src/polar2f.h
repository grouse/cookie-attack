#ifndef POLAR2F
#define POLAR2F

class Polar2f {
	public:
		Polar2f(float, float);
		~Polar2f();

		void rotate(float);
		float getAngle();
		float getLength();

	private:
		float angle, length;

};

#endif
