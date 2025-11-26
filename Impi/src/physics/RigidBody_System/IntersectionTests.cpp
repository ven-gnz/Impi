#include "IntersectionTests.h"

using namespace Impi;

bool IntersectionTests::sphereAndHalfSpace(
	const CollisionSphere& sphere,
	const CollisionPlane& plane)
{
	real ballDist = plane.direction * sphere.getAxis(3) - sphere.radius;
}

bool IntersectionTests::sphereAndSphere(
	const CollisionSphere& one,
	const CollisionSphere& two)
{
	Vector3 midline = one.getAxis(3) - two.getAxis(3);

	return midline.squared_Magnitude() < (one.radius + two.radius) * (one.radius + two.radius);
}



bool IntersectionTests::testSeparatingAxisOverlap(
	const CollisionBox& one,
	const CollisionBox& two,
	const Vector3& axis,
	const Vector3& tocenter
)
{

	real oneProjected = one.projectToAxis(axis);
	real twoProjected = two.projectToAxis(axis);

	real distance = real_abs(tocenter * axis);
	return(distance < oneProjected + twoProjected);

}

bool IntersectionTests::boxAndBox(
	const CollisionBox& one,
	const CollisionBox& two)
{
	// Separating axis theorem in three dimensions : both box axis, then the 9 cross products
	Vector3 centerOffset = two.getAxis(3) - one.getAxis(3);

	for (int i = 0; i < 3; i++)
	{
		if (!testSeparatingAxisOverlap(one, two, one.getAxis(i), centerOffset)) return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (!testSeparatingAxisOverlap(one, two, two.getAxis(i), centerOffset)) return false;
	}
	// i for iterating the first box axis, j for iterating the other boxes axises. Wild looking but pretty standard.
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (!testSeparatingAxisOverlap(
				one,
				two,
				one.getAxis(i).cross(two.getAxis(j)),
				centerOffset))
			{
				return false;
			}
		}
	}

}

bool IntersectionTests::boxAndHalfSpace(
	const CollisionBox& box,
	const CollisionPlane& plane
)
{
	real projectedRadius = box.projectToAxis(plane.direction);
	real boxDistance = plane.direction * box.getAxis(3) - projectedRadius;

	return boxDistance <= plane.offset;
}

