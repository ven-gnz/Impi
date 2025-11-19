#include "Contact.h"

namespace Impi
{



struct CollisionData
{
	Contact* contacts;
	unsigned contactsLeft;
};

class CollisionPrimitive
{
public:
	RigidBody* body;
	Matrix4 offset;

};


class CollisionSphere : public CollisionPrimitive
{
public:

	real radius;
};


}