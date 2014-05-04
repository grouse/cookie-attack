#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb_image.h>
#include <SDL2/SDL_opengl.h>

#include "entity.h"
#include "component.h"

namespace JEngine {
	class Texture : public Component {
		public:
			Texture(const char*);
			virtual ~Texture();

			virtual bool canAttach(Entity&);

			const char* filename;
			GLuint GLtex;
			int width, height;
			int components;

			GLuint vbo, ibo;


	};
}

#endif
