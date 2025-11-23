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

bool IntersectionTests::boxAndBox(
	const CollisionBox& one,
	const CollisionBox& two)
{

}