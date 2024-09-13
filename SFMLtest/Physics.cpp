#include "Collider.h"
#include "CollisionInfo.h"
#include "Vector.h"
#include "Physics.h"

namespace aengine {
	const float Physics::g = -9.81f;
	const float Physics::airResistance = 0.045f;
	const int Physics::fixedUpdateIntervalMs = 50;

	bool Physics::AreOverlapping(const CircleCollider* c1, const CircleCollider* c2, CollisionInfo* outInfo) {
		Vectorf delta = (c2->worldCenter - c1->worldCenter);
		float distance = delta.getLength();
		bool areover = distance <= c1->radius + c2->radius;
		if (areover)
			outInfo = new CollisionInfo(delta, (c1->worldCenter + c2->worldCenter) / 2.f); // pos temp calculation
		return areover;
	}

	bool Physics::AreOverlapping(const RectCollider* c1, const CircleCollider* c2, CollisionInfo* outInfo) {
		throw std::exception("Non-implemented function Physics::AreOverlapping (2) cannot be invoked.");
		
		return false;
	}

	bool Physics::AreOverlapping(const RectCollider* c1, const RectCollider* c2, CollisionInfo* outInfo) {
		Vectorf pos;
		Vectorf normal;

		//if (c1->)

		return false;
	}
}