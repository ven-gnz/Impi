#include "Contact.h"

namespace Impi
{

struct CollisionData
{
	Contact* contacts;
	int contactsLeft;
	unsigned contactCount;
	real friction;
	real restitution;
	real tolerance;
};

class CollisionPrimitive
{
public:

	
	friend class CollisionDetector;

	RigidBody* body;
	Matrix4 offset;
	Vector3 getAxis(unsigned index) const
	{
		return transform.getAxisVector(index);
	}

protected:
	Matrix4 transform;
};


class CollisionSphere : public CollisionPrimitive
{
public:

	real radius;
};


}