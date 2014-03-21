#include "render_system.h"

namespace JEngine {
	
	RenderSystem::RenderSystem(GameObjects* objects, SDL_Window* w) : System(objects) {
		window = w;
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

			glColor3f(255, 255, 255);

			glVertexPointer(
				3, GL_FLOAT, 0,
				s->vertices.data()
			);

			glDrawArrays(GL_QUADS, 0, 4);
			
			glTranslatef(-e->x, -e->y, -e->z);
		}
		
		SDL_GL_SwapWindow(window);
	}
}
