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
};

}