#pragma once
#include <math/Vector3.h>


namespace Impi
{



struct BoundingSphere
{
	Vector3 center;
	real radius;

public:

	BoundingSphere(const Vector3& center, real radius);

	BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

	bool overlaps(const BoundingSphere* other) const;

};


}