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
				
				// transform shape to entity (world) space
				transformToEntity(s1, e1, 1);
				transformToEntity(s2, e2, 1);

				// calculate the 4 axis
				float a1x, a1y;
				calculateAxis(&a1x, &a1y, s1->vertices[3], s1->vertices[4], s1->vertices[0], s1->vertices[1]);

				float a2x, a2y;
				calculateAxis(&a2x, &a2y, s1->vertices[3], s1->vertices[4], s1->vertices[6], s1->vertices[7]);

				float a3x, a3y;
				calculateAxis(&a3x, &a3y, s2->vertices[0], s2->vertices[1], s2->vertices[9], s2->vertices[10]);

				float a4x, a4y;
				calculateAxis(&a4x, &a4y, s2->vertices[0], s2->vertices[1], s2->vertices[3], s2->vertices[4]);
				
				
				// calculate projections
				
				// axis 1
				
				// A.UL
				float paa1ulx, paa1uly;
				calculateProjection(&paa1ulx, &paa1uly, s1->vertices[0], s1->vertices[1], a1x, a1y);

				// A.UR
				float paa1urx, paa1ury;
				calculateProjection(&paa1urx, &paa1ury, s1->vertices[3], s1->vertices[4], a1x, a1y);

				// A.LR
				float paa1lrx, paa1lry;
				calculateProjection(&paa1lrx, &paa1lry, s1->vertices[6], s1->vertices[7], a1x, a1y);

				// A.LL
				float paa1llx, paa1lly;
				calculateProjection(&paa1llx, &paa1lly, s1->vertices[9], s1->vertices[10], a1x, a1y);

				
				// B.UL
				float pba1ulx, pba1uly;
				calculateProjection(&pba1ulx, &pba1uly, s2->vertices[0], s2->vertices[1], a1x, a1y);

				// B.UR
				float pba1urx, pba1ury;
				calculateProjection(&pba1urx, &pba1ury, s2->vertices[3], s2->vertices[4], a1x, a1y);

				// B.LR
				float pba1lrx, pba1lry;
				calculateProjection(&pba1lrx, &pba1lry, s2->vertices[6], s2->vertices[7], a1x, a1y);

				// B.LL
				float pba1llx, pba1lly;
				calculateProjection(&pba1llx, &pba1lly, s2->vertices[9], s2->vertices[10], a1x, a1y);


				// axis 2
				
				// A.UL
				float paa2ulx, paa2uly;
				calculateProjection(&paa2ulx, &paa2uly, s1->vertices[0], s1->vertices[1], a2x, a2y);

				// A.UR
				float paa2urx, paa2ury;
				calculateProjection(&paa2urx, &paa2ury, s1->vertices[3], s1->vertices[4], a2x, a2y);

				// A.LR
				float paa2lrx, paa2lry;
				calculateProjection(&paa2lrx, &paa2lry, s1->vertices[6], s1->vertices[7], a2x, a2y);

				// A.LL
				float paa2llx, paa2lly;
				calculateProjection(&paa2llx, &paa2lly, s1->vertices[9], s1->vertices[10], a2x, a2y);

				
				// B.UL
				float pba2ulx, pba2uly;
				calculateProjection(&pba2ulx, &pba2uly, s2->vertices[0], s2->vertices[1], a2x, a2y);

				// B.UR
				float pba2urx, pba2ury;
				calculateProjection(&pba2urx, &pba2ury, s2->vertices[3], s2->vertices[4], a2x, a2y);

				// B.LR
				float pba2lrx, pba2lry;
				calculateProjection(&pba2lrx, &pba2lry, s2->vertices[6], s2->vertices[7], a2x, a2y);

				// B.LL
				float pba2llx, pba2lly;
				calculateProjection(&pba2llx, &pba2lly, s2->vertices[9], s2->vertices[10], a2x, a2y);


				// axis 3
				
				// A.UL
				float paa3ulx, paa3uly;
				calculateProjection(&paa3ulx, &paa3uly, s1->vertices[0], s1->vertices[1], a3x, a3y);

				// A.UR
				float paa3urx, paa3ury;
				calculateProjection(&paa3urx, &paa3ury, s1->vertices[3], s1->vertices[4], a3x, a3y);

				// A.LR
				float paa3lrx, paa3lry;
				calculateProjection(&paa3lrx, &paa3lry, s1->vertices[6], s1->vertices[7], a3x, a3y);

				// A.LL
				float paa3llx, paa3lly;
				calculateProjection(&paa3llx, &paa3lly, s1->vertices[9], s1->vertices[10], a3x, a3y);

				
				// B.UL
				float pba3ulx, pba3uly;
				calculateProjection(&pba3ulx, &pba3uly, s2->vertices[0], s2->vertices[1], a3x, a3y);

				// B.UR
				float pba3urx, pba3ury;
				calculateProjection(&pba3urx, &pba3ury, s2->vertices[3], s2->vertices[4], a3x, a3y);

				// B.LR
				float pba3lrx, pba3lry;
				calculateProjection(&pba3lrx, &pba3lry, s2->vertices[6], s2->vertices[7], a3x, a3y);

				// B.LL
				float pba3llx, pba3lly;
				calculateProjection(&pba3llx, &pba3lly, s2->vertices[9], s2->vertices[10], a3x, a3y);


				// axis 4
				
				// A.UL
				float paa4ulx, paa4uly;
				calculateProjection(&paa4ulx, &paa4uly, s1->vertices[0], s1->vertices[1], a4x, a4y);

				// A.UR
				float paa4urx, paa4ury;
				calculateProjection(&paa4urx, &paa4ury, s1->vertices[3], s1->vertices[4], a4x, a4y);

				// A.LR
				float paa4lrx, paa4lry;
				calculateProjection(&paa4lrx, &paa4lry, s1->vertices[6], s1->vertices[7], a4x, a4y);

				// A.LL
				float paa4llx, paa4lly;
				calculateProjection(&paa4llx, &paa4lly, s1->vertices[9], s1->vertices[10], a4x, a4y);

				
				// B.UL
				float pba4ulx, pba4uly;
				calculateProjection(&pba4ulx, &pba4uly, s2->vertices[0], s2->vertices[1], a4x, a4y);

				// B.UR
				float pba4urx, pba4ury;
				calculateProjection(&pba4urx, &pba4ury, s2->vertices[3], s2->vertices[4], a4x, a4y);

				// B.LR
				float pba4lrx, pba4lry;
				calculateProjection(&pba4lrx, &pba4lry, s2->vertices[6], s2->vertices[7], a4x, a4y);

				// B.LL
				float pba4llx, pba4lly;
				calculateProjection(&pba4llx, &pba4lly, s2->vertices[9], s2->vertices[10], a4x, a4y);

				// calculate projected scalar values

				// axis 1
				float psaa1ul = calculateScalar(paa1ulx, paa1uly, a1x, a1y);
				float psaa1ur = calculateScalar(paa1urx, paa1ury, a1x, a1y);
				float psaa1lr = calculateScalar(paa1lrx, paa1lry, a1x, a1y);
				float psaa1ll = calculateScalar(paa1llx, paa1lly, a1x, a1y);
				
				float psba1ul = calculateScalar(pba1ulx, pba1uly, a1x, a1y);
				float psba1ur = calculateScalar(pba1urx, pba1ury, a1x, a1y);
				float psba1lr = calculateScalar(pba1lrx, pba1lry, a1x, a1y);
				float psba1ll = calculateScalar(pba1llx, pba1lly, a1x, a1y);
				
				// axis 2
				float psaa2ul = calculateScalar(paa2ulx, paa2uly, a2x, a2y);
				float psaa2ur = calculateScalar(paa2urx, paa2ury, a2x, a2y);
				float psaa2lr = calculateScalar(paa2lrx, paa2lry, a2x, a2y);
				float psaa2ll = calculateScalar(paa2llx, paa2lly, a2x, a2y);
		
				float psba2ul = calculateScalar(pba2ulx, pba2uly, a2x, a2y);
				float psba2ur = calculateScalar(pba2urx, pba2ury, a2x, a2y);
				float psba2lr = calculateScalar(pba2lrx, pba2lry, a2x, a2y);
				float psba2ll = calculateScalar(pba2llx, pba2lly, a2x, a2y);

				// axis 3
				float psaa3ul = calculateScalar(paa3ulx, paa3uly, a3x, a3y);
				float psaa3ur = calculateScalar(paa3urx, paa3ury, a3x, a3y);
				float psaa3lr = calculateScalar(paa3lrx, paa3lry, a3x, a3y);
				float psaa3ll = calculateScalar(paa3llx, paa3lly, a3x, a3y);
				
				float psba3ul = calculateScalar(pba3ulx, pba3uly, a3x, a3y);
				float psba3ur = calculateScalar(pba3urx, pba3ury, a3x, a3y);
				float psba3lr = calculateScalar(pba3lrx, pba3lry, a3x, a3y);
				float psba3ll = calculateScalar(pba3llx, pba3lly, a3x, a3y);
				
				// axis 4
				float psaa4ul = calculateScalar(paa4ulx, paa4uly, a4x, a4y);
				float psaa4ur = calculateScalar(paa4urx, paa4ury, a4x, a4y);
				float psaa4lr = calculateScalar(paa4lrx, paa4lry, a4x, a4y);
				float psaa4ll = calculateScalar(paa4llx, paa4lly, a4x, a4y);
				
				float psba4ul = calculateScalar(pba4ulx, pba4uly, a4x, a4y);
				float psba4ur = calculateScalar(pba4urx, pba4ury, a4x, a4y);
				float psba4lr = calculateScalar(pba4lrx, pba4lry, a4x, a4y);
				float psba4ll = calculateScalar(pba4llx, pba4lly, a4x, a4y);



				// find min and max projected scalar
				
				// min/max a
				float minaa1 = findMin(psaa1ul, psaa1ur, psaa1lr, psaa1ll);
				float minaa2 = findMin(psaa2ul, psaa2ur, psaa2lr, psaa2ll);
				float minaa3 = findMin(psaa3ul, psaa3ur, psaa3lr, psaa3ll);
				float minaa4 = findMin(psaa4ul, psaa4ur, psaa4lr, psaa4ll);

				float maxaa1 = findMax(psaa1ul, psaa1ur, psaa1lr, psaa1ll);
				float maxaa2 = findMax(psaa2ul, psaa2ur, psaa2lr, psaa2ll);
				float maxaa3 = findMax(psaa3ul, psaa3ur, psaa3lr, psaa3ll);
				float maxaa4 = findMax(psaa4ul, psaa4ur, psaa4lr, psaa4ll);

				// min/max b
				float minba1 = findMin(psba1ul, psba1ur, psba1lr, psba1ll);
				float minba2 = findMin(psba2ul, psba2ur, psba2lr, psba2ll);
				float minba3 = findMin(psba3ul, psba3ur, psba3lr, psba3ll);
				float minba4 = findMin(psba4ul, psba4ur, psba4lr, psba4ll);

				float maxba1 = findMax(psba1ul, psba1ur, psba1lr, psba1ll);
				float maxba2 = findMax(psba2ul, psba2ur, psba2lr, psba2ll);
				float maxba3 = findMax(psba3ul, psba3ur, psba3lr, psba3ll);
				float maxba4 = findMax(psba4ul, psba4ur, psba4lr, psba4ll);
				
				// finally, check for collision
				
				bool collision = true;
				collision = collision && minba1 <= maxaa1 && maxba1 >= minaa1;
				collision = collision && minba2 <= maxaa2 && maxba2 >= minaa2;
				collision = collision && minba3 <= maxaa3 && maxba3 >= minaa3;
				collision = collision && minba4 <= maxaa4 && maxba4 >= minaa4;

				if (collision) {
					c1->response(e1, e2, objects);
					c2->response(e2, e1, objects);
				}
		
				transformToEntity(s1, e1, -1);
				transformToEntity(s2, e2, -1);
			}
		}
	}

	void CollisionSystem::transformToEntity(Shape* s, Entity* e, int sign) {
		s->vertices[0] += e->pos.x*sign;
		s->vertices[1] += e->pos.y*sign;

		s->vertices[3] += e->pos.x*sign;
		s->vertices[4] += e->pos.y*sign;

		s->vertices[6] += e->pos.x*sign;
		s->vertices[7] += e->pos.y*sign;

		s->vertices[9] += e->pos.x*sign;
		s->vertices[10] += e->pos.y*sign;
	}

	void CollisionSystem::calculateAxis(float* ax, float* ay, float v1x, float v1y, float v2x, float v2y) {
		*ax = v1x - v2x;
		*ay = v1y - v2y;
	}

	void CollisionSystem::calculateProjection(float* px, float* py, float v1x, float v1y, float v2x, float v2y) {
		float projection = (v1x * v2x + v1y * v2y) / (v2x * v2x + v2y * v2y);

		*px = projection*v2x;
		*py = projection*v2y;
	}

	float CollisionSystem::calculateScalar(float v1x, float v1y, float v2x, float v2y) {
		return v1x * v2x + v1y * v2y;
	}

	float CollisionSystem::findMin(float a, float b, float c, float d) {
		float min = a;
		min = (min > b) ? b : min;
		min = (min > c) ? c : min;
		min = (min > d) ? d : min;

		return min;
	}

	float CollisionSystem::findMax(float a, float b, float c, float d) {
		float max = a;
		max = (max < b) ? b : max;
		max = (max < c) ? c : max;
		max = (max < d) ? d : max;

		return max;
	}
}
