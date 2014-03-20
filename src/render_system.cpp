#include "render_system.h"

namespace JEngine {
	
	RenderSystem::RenderSystem() : System(System::RENDER) {}

	RenderSystem::~RenderSystem() {}

	void RenderSystem::update(float dt) {
		for (auto it = components[Component::SHAPE].begin(); it != components[Component::SHAPE].end(); it++) {
			Shape* s = (Shape*) (*it);
			Entity* e = entities[s->owner];

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
	}
}
