#include "collision_system.h"

#include <iostream>

namespace JEngine {

	CollisionSystem::CollisionSystem(GameObjects* objects) : System(objects) {}
	CollisionSystem::~CollisionSystem() {}

	void CollisionSystem::update(float dt) {

		auto itr = objects->components[Component::COLLISION].rbegin();
		itr++;

		for (auto it = objects->components[Component::COLLISION].begin(); it != objects->components[Component::COLLISION].end(); it++) {
			auto jt = it;
			
			for (jt++; jt != objects->components[Component::COLLISION].end(); jt++) {
				Collision* c1 = (Collision*) (*it);
				Collision* c2 = (Collision*) (*jt);

				Entity* e1 = c1->owner;
				Entity* e2 = c2->owner;

				Shape* s1 = (Shape*) (e1->components[Component::SHAPE]);
				Shape* s2 = (Shape*) (e2->components[Component::SHAPE]);
				
				// separating axis theorem
				glm::vec3 a[4];
				a[0] = glm::vec3(s1->vertices[0], s1->vertices[1], 0.0f) + e1->pos;
				a[1] = glm::vec3(s1->vertices[3], s1->vertices[4], 0.0f) + e1->pos;
				a[2] = glm::vec3(s1->vertices[6], s1->vertices[7], 0.0f) + e1->pos;
				a[3] = glm::vec3(s1->vertices[9], s1->vertices[10], 0.0f) + e1->pos;

				glm::vec3 b[4];
				b[0] = glm::vec3(s2->vertices[0], s2->vertices[1], 0.0f) + e2->pos;
				b[1] = glm::vec3(s2->vertices[3], s2->vertices[4], 0.0f) + e2->pos;
				b[2] = glm::vec3(s2->vertices[6], s2->vertices[7], 0.0f) + e2->pos;
				b[3] = glm::vec3(s2->vertices[9], s2->vertices[10], 0.0f) + e2->pos;

				glm::vec3 axes[4];
				axes[0] = glm::normalize(a[1] - a[0]);
				axes[1] = glm::normalize(a[1] - a[2]);
				axes[2] = glm::normalize(b[0] - b[3]);
				axes[3] = glm::normalize(b[0] - b[1]);

				bool collision = true;

				float overlapScalar = 1000.0f;
				glm::vec3 overlapVec = glm::vec3(0.0f);

				for (unsigned int i = 0; i < 4 && collision; i++) {
					glm::vec3 axis = perp(axes[i]);
					glm::vec3 a_projection = project(a, axis);
					glm::vec3 b_projection = project(b, axis);

					collision = overlaps(a_projection, b_projection);
				   	if (collision) {
						float o = getOverlap(a_projection, b_projection);

						if (o < overlapScalar) {
							overlapScalar = o;
							overlapVec = axis;
						}
					}	
				}
				if (collision) {
					c1->response(e1, e2, overlapScalar*overlapVec, objects);
					c2->response(e2, e1, overlapScalar*overlapVec, objects);
				}
				
			}
		}
	}


	glm::vec3 CollisionSystem::project(glm::vec3* shape, glm::vec3 axis) {
		float min = glm::dot(axis, shape[0]);
		float max = min;

		for (unsigned int i = 0; i < 4; i++) {
			float tmp = glm::dot(axis, shape[i]);

			if (tmp < min) {
				min = tmp;
			} 
			
			if (tmp > max) {
				max = tmp;
			}
		}

		return glm::vec3(min, max, 0.0f);
	}

	bool CollisionSystem::overlaps(glm::vec3 a, glm::vec3 b) {
		if (contains(a.x, b)) return true;
		if (contains(a.y, b)) return true;
		if (contains(b.x, a)) return true;
		if (contains(b.y, a)) return true;

		return false;
	}

	float CollisionSystem::getOverlap(glm::vec3 a, glm::vec3 b) {
		float overlap;
		
		if (a.y >= b.x && a.x <= b.x || b.y >= a.x && b.x <= a.x) {
			float overlapR = a.y - b.x;
			float overlapL = b.y - a.x;

			overlap = (overlapR < overlapL) ? overlapR : overlapL;
		} else {
			float overlapR = b.y - a.y;
			float overlapL = b.x - a.x;

			overlap = (overlapR < overlapL) ? overlapR : overlapL;
		}
	

		return overlap;
	}

	bool CollisionSystem::contains(float n, glm::vec3 r) {
		float a = r.x, b = r.y;
		if (b < a) {
			a = b;
			b = r.x;
		}

		return (n >= a && n <= b);
	}

	glm::vec3 CollisionSystem::perp(glm::vec3 v) {
		return glm::vec3(v.y, -v.x, 0.0f);
	}
}
