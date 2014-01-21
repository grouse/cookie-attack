#include "position.h"

namespace JEngine {
	
	Position::Position(float x, float y, float z) : Component(Component::POSITION) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Position::~Position() {}

	bool Position::canAttach(Entity& e) {
		return true;
	}

}
