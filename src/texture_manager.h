#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <list>

#include <stb_image.h>

#include "texture.h"

namespace JEngine {
	class TextureManager {
		std::list<Texture*> loaded;

	public:
		TextureManager();
		~TextureManager();

		Texture* load(char*);
		void remove(char*);	
	
	};
}

#endif
