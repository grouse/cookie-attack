#include "texture.h"

namespace JEngine {
	
	Texture::Texture(char* filename) : Component(Component::TEXTURE) {
		
	}

	Texture::~Texture() {
	
	}

	bool Texture::canAttach(Entity& e) {
		return true;
	}
}
