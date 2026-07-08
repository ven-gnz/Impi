#pragma once
#include <physics/RigidBody_System/CollisionPrimitives.h>

namespace Impi
{

	struct PotentialContact
	{
		CollisionPrimitive* first;
		CollisionPrimitive* second;
	};


class BroadPhase

{
public:
	virtual ~BroadPhase() = default;
	virtual void clear() = 0;
	virtual void insert(CollisionPrimitive* p) = 0;

	virtual unsigned generatePairs(PotentialContact*, unsigned limit) = 0;

	inline bool overlaps(const AABB& a, const AABB& b)
	{
		return
			a.min.x <= b.max.x &&
			a.max.x >= b.min.x &&

			a.min.y <= b.max.y &&
			a.max.y >= b.min.y &&

			a.min.z <= b.max.z &&
			a.max.z >= b.min.z;
	}

};

}