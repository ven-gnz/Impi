#include "src/physics/RigidBody_System/BoundingVolumes.h"

using namespace Impi;



bool BoundingSphere::overlaps(const BoundingSphere* other) const
{
	real distanceSquared = (center - other->center).squared_Magnitude();
	return distanceSquared < (radius + other->radius) * (radius + other->radius);
}


