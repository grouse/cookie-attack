#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image.h>

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Texture : public Component {
		public:
			Texture(char*);
			virtual ~Texture();

			char* filename;
			GLuint GLtex;
			int width, height;
			int components;
	};
}

#endif
