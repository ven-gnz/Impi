#pragma once
#include "CollisionPrimitives.h"

namespace Impi
{
	struct CollisionData
	{
		Contact* contacts;
		int contactsLeft;
		unsigned contactCount;
		real friction;
		real restitution;
		real tolerance;

		bool hasMoreContacts();
		void reset(unsigned maxContacts);
		void addContacts(unsigned count);
	};


	class CollisionDetector
	{
	public:

		static unsigned sphereAndSphere
		(const CollisionSphere& one,
			const CollisionSphere& two,
			CollisionData* data
		);

		unsigned sphereAndHalfSpace(const CollisionSphere& sphere,
			const CollisionPlane& plane,
			CollisionData* data);

		unsigned sphereAndTruePlane(const CollisionSphere& sphere,
			const CollisionPlane& plane,
			CollisionData* data);

		unsigned boxAndHalfSpace(
			const CollisionBox& box,
			const CollisionPlane& plane,
			CollisionData* data
		);

		unsigned boxAndSphere(
			const CollisionBox& box,
			const CollisionSphere& sphere,
			CollisionData* data
		);

		unsigned boxAndPoint(
			const CollisionBox& box,
			const Vector3& point,
			CollisionData* data);

	};

}