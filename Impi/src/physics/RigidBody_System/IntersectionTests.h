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


	static bool boxAndHalfSpace(
		const CollisionBox& box,
		const CollisionPlane& plane
	);

	/*
	* Separating Axis Theorem - helper for polygon shapes
	*/
	static bool testSeparatingAxisOverlap(
		const CollisionBox& one,
		const CollisionBox& two,
		const Vector3& axis,
		const Vector3& tocenter
	);


	/*
	* Orienteding Bounding Box OBB intersection test, using the Separating Axis Theorem.
	* Boxes intersect if there are no separating axis among the 15 possible ones:
	* 3 for box one, 3 for box two, 9 for cross product
	* Hyperspace stuffs will have to wait
	*/
	static bool boxAndBox(
		const CollisionBox& one,
		const CollisionBox& two);

};


}