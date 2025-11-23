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

	static bool boxAndBox(
		const CollisionBox& one,
		const CollisionBox& two);

};


}