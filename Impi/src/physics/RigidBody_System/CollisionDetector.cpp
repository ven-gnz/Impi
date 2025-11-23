#include "IntersectionTests.h"
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

unsigned CollisionDetector::sphereAndHalfSpace(const CollisionSphere& sphere,
	const CollisionPlane& plane,
	CollisionData* data)
{

		if (data->contactsLeft <= 0) return 0;

		Vector3 position = sphere.getAxis(3);
		real ballDistance =
			plane.direction * position -
			sphere.radius - plane.offset;
		if (ballDistance >= 0) return 0;

		Contact* contact = data->contacts;
		contact->contactNormal = plane.direction;
		contact->penetration = -ballDistance;
		contact->contactPoint = position - plane.direction * (ballDistance + sphere.radius);

		contact->body[0] = sphere.body;
		contact->body[1] = NULL;
		contact->restitution = data->restitution;
		contact->friction = data->friction;

		return 1;
	
}

unsigned CollisionDetector::sphereAndTruePlane(const CollisionSphere& sphere,
	const CollisionPlane& plane,
	CollisionData* data)
{
	if (data->contactsLeft <= 0) return 0;

	Vector3 position = sphere.getAxis(3);

	real centerDistance = plane.direction * position - plane.offset;

	if (centerDistance * centerDistance > sphere.radius * sphere.radius) return 0;

	Vector3 normal = plane.direction;
	real penetration = -centerDistance;
	// check which side of the plane
	if (centerDistance < 0)
	{
		normal *= -1;
		penetration = -penetration;
	}

	penetration += sphere.radius;

	//Update contact
	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->penetration = penetration;
	contact->contactPoint = position - plane.direction * centerDistance;
	//write data
	contact->body[0] = sphere.body;
	contact->body[1] = NULL;
	contact->restitution = data->restitution;
	contact->friction = data->friction;

	return 1;

}

unsigned CollisionDetector::boxAndHalfSpace(
	const CollisionBox& box,
	const CollisionPlane& plane,
	CollisionData* data
)
{

	if (data->contactsLeft >= 0) return 0;

	
}