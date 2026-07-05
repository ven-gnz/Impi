#include "src/physics/RigidBody_System/BoundingVolumes.h"

using namespace Impi;



bool BoundingSphere::overlaps(const BoundingSphere* other) const
{
	real distanceSquared = (center - other->center).squared_Magnitude();
	return distanceSquared < (radius + other->radius) * (radius + other->radius);
}

BoundingSphere::BoundingSphere(const Vector3& centre, real radius)
{
	BoundingSphere::center = centre;
	BoundingSphere::radius = radius;
}

BoundingSphere::BoundingSphere(const BoundingSphere& one, const BoundingSphere& two)
{

	Vector3 centerOffset = two.center - one.center;
	real distance = centerOffset.squared_Magnitude();
	real difference_in_radius = two.radius - one.radius;

	// suppose larger sphere encompasses the smaller
	if (difference_in_radius * difference_in_radius >= distance)
	{
		if (one.radius > two.radius)
		{
			center = one.center;
			radius = one.radius;
		}
		else
		{
			center = two.center;
			radius = two.radius;
		}
	}
	//spheres are partially overlapping
	else
	{
		distance = real_sqrt(distance);
		radius = (distance + one.radius + two.radius) * ((real)0.5);

		center = one.center;
		if (distance > 0)
		{
			center += centerOffset * ((radius - one.radius) / distance);
		}
	}

}




real BoundingSphere::getGrowth(const BoundingSphere& other) const
{
	BoundingSphere newSphere(*this, other);

	// We return a value proportional to the change in surface
	// area of the sphere.
	return newSphere.radius * newSphere.radius - radius * radius;
}