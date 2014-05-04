#include "render_system.h"

#include <iostream>

namespace JEngine {
	
	RenderSystem::RenderSystem(GameObjects* objects, SDL_Window* w) : System(objects) {
		window = w;

		uv[0] = 0.0f;
		uv[1] = 0.0f;

		uv[2] = 32.0f;
		uv[3] = 0.0f;

		uv[4] = 32.0f;
		uv[5] = 32.0f;

		uv[6] = 0.0f;
		uv[7] = 32.0f;
	}

	RenderSystem::~RenderSystem() {}

	void RenderSystem::update(float dt) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (auto it = objects->components[Component::SHAPE].begin(); it != objects->components[Component::SHAPE].end(); it++) {
			Shape* s = (Shape*) (*it);
			Entity* e = s->owner;

			glLoadIdentity();
			glTranslatef(e->x, e->y, e->z);

			if (e->components[Component::TEXTURE] != 0) {
				Texture* t = (Texture*) e->components[Component::TEXTURE];
				glBindTexture(GL_TEXTURE_2D, t->GLtex);
	
				glTexCoordPointer(2, GL_FLOAT, sizeof(float)*6, (GLvoid*)(sizeof(float)*3));
			} else {
				glColor3f(255, 255, 255);
			}

			glVertexPointer(
				3, GL_FLOAT, 0,
				s->vertices.data()
			);

			glDrawArrays(GL_QUADS, 0, 4);

			if (e->components[Component::TEXTURE] != 0)
				glBindTexture(GL_TEXTURE_2D, 0);
			
			glTranslatef(-e->x, -e->y, -e->z);
		}
		
		SDL_GL_SwapWindow(window);
	}
}
