#pragma once
#include "CollisionPrimitives.h"

namespace Impi
{



class IntersectionTests
{
public:

	static bool sphereAndHalfSpace(
		const CollisionSphere& sphere,
		const CollisionPlane& plane);
	
	static bool sphereAndSphere(
		const CollisionSphere& one,
		const CollisionSphere& two);

	/*
	* Separating Axis Theorem - helper for polygon shapes
	*/
	static bool testSeparatingAxisOverlap(
		const CollisionBox& one,
		const CollisionBox& two,
		const Vector3& axis,
		const Vector3& tocenter
	);

	static bool boxAndBox(
		const CollisionBox& one,
		const CollisionBox& two);

};


}