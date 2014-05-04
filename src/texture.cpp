#include "texture.h"

namespace JEngine {
	
	Texture::Texture(const char* filename) : Component(Component::TEXTURE) {
		this->filename = filename;
	}

	Texture::~Texture() {
	
	}

	bool Texture::canAttach(Entity& e) {
		return true;
	}
}
