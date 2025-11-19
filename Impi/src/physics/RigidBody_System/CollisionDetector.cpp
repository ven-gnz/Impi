#include "CollisionDetector.h"

using namespace Impi;

unsigned CollisionDetector::sphereAndSphere(
	const CollisionSphere& one,
	const CollisionSphere& two,
	CollisionData* data)
{
	
	if (data->contactsLeft <= 0) return 0;

	Vector3 p1 = one.getAxis(3);
	Vector3 p2 = one.getAxis(3);

	Vector3 mid = p1 - p2;
	real size = mid.magnitude();

	if (size <= 0.0f || size >= one.radius + two.radius) return 0;

	Vector3 normal = mid * ((real)1.0 / size);
	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->contactPoint = p1 + mid * (real)0.5;
	contact->penetration = (one.radius + two.radius - size);

	contact->body[0] = one.body;
	contact->body[1] = two.body;
	contact->restitution = data->restitution;
	contact->friction = data->friction;
}