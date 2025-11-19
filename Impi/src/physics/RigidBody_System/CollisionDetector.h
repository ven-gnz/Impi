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
};

}