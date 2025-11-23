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

class CollisionPlane : public CollisionPrimitive
{
public:
	Vector3 direction;
	real offset;
};

class CollisionBox : public CollisionPrimitive
{
public:
	Vector3 halfSize;
};


}