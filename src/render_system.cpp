#include "render_system.h"

#include <iostream>

namespace JEngine {
	
	RenderSystem::RenderSystem(GameObjects* objects, SDL_Window* w) : System(objects) {
		window = w;

		uv[0] = 0.0f;
		uv[1] = 0.0f;

		uv[2] = 1.0f;
		uv[3] = 0.0f;

		uv[4] = 1.0f;
		uv[5] = 1.0f;

		uv[6] = 0.0f;
		uv[7] = 1.0f;

	}

	RenderSystem::~RenderSystem() {}

	void RenderSystem::update(float dt) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (auto it = objects->components[Component::SHAPE].begin(); it != objects->components[Component::SHAPE].end(); it++) {
			Shape* s = (Shape*) (*it);
			Entity* e = s->owner;

			glLoadIdentity();
			glTranslatef(e->pos.x, e->pos.y, e->pos.z);


			glVertexPointer(
				3, GL_FLOAT, 0,
				s->vertices.data()
			);
			
			if (e->components[Component::TEXTURE] != 0) {
				Texture* t = (Texture*) e->components[Component::TEXTURE];
				glBindTexture(GL_TEXTURE_2D, t->GLtex);
				glTexCoordPointer(2, GL_FLOAT, 0, uv);

				glDrawArrays(GL_QUADS, 0, 4);
				glBindTexture(GL_TEXTURE_2D, 0);
			} else {
				glColor3f(255, 255, 255);
				glDrawArrays(GL_QUADS, 0, 4);
			}

			
			glTranslatef(-e->pos.x, -e->pos.y, -e->pos.z);
		}
		
		SDL_GL_SwapWindow(window);
	}
}
