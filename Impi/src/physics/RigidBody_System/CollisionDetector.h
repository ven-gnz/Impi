#pragma once
#include "CollisionPrimitives.h"

namespace Impi
{



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

	};

}