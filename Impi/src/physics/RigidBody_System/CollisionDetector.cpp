#include "IntersectionTests.h"
#include "CollisionDetector.h"


using namespace Impi;

bool CollisionData::hasMoreContacts() { return contacts > 0; }
void CollisionData::reset(unsigned maxContacts)
{
	contactsLeft = maxContacts;
	contactCount = 0;
	contacts = first_contact_in_array;
}
void CollisionData::addContacts(unsigned count)
{
	contactsLeft -= count;
	contactCount += count;
	// increment index ptr
	contacts += count;
}

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

	data->addContacts(1);
	return 1;
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
		data->addContacts(1);
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

	if (!IntersectionTests::boxAndHalfSpace(box, plane))
	{
		return 0;
	}

	// Multiplication factors as binary words of n=3
	static real mul[8][3] =
	{
		{1,1,1},{1,1,-1}, {1,-1,1}, {1,-1,-1},		//000-011
		{-1,1,1}, {-1,1,-1}, {-1,-1,1}, {-1,-1,-1}  //100-111
	};

	Contact* contact = data->contacts;
	unsigned contactsused = 0;

	for (unsigned i = 0; i < 8; i++)
	{
		Vector3 vertexPos(mul[i][0], mul[i][1], mul[i][2]);
		vertexPos.componentProductUpdate(box.halfSize);
		vertexPos = box.getTransform().transform(vertexPos);

		real vertexDistance = vertexPos * plane.direction;

		if (vertexDistance <= plane.offset)
		{
			/*
			* Contact point is halfway between vertex and plane.
			* Get the direction, multiply by separation of distances and translate by the vertex loc.
			*/
			contact->contactPoint = plane.direction;
			contact->contactPoint *= (vertexDistance - plane.offset);
			contact->contactPoint += vertexPos;
			contact->contactNormal = plane.direction;
			contact->penetration = plane.offset - vertexDistance;

			contact->body[0] = box.body;
			contact->body[1] = NULL;
			contact->friction = data->friction;
			contact->restitution = data->restitution;

			contact++;
			contactsused++;
			if (contactsused == (unsigned)data->contactsLeft) return contactsused;

		}
	}

	data->addContacts(contactsused);
	return contactsused;


}



unsigned CollisionDetector::boxAndSphere(
	const CollisionBox& box,
	const CollisionSphere& sphere,
	CollisionData* data
)
{
	Vector3 center = sphere.getAxis(3);
	Vector3 relCenter = box.getTransform().transformInverse(center);

	if (real_abs(relCenter.x) - sphere.radius > box.halfSize.x ||
		real_abs(relCenter.y) - sphere.radius > box.halfSize.y ||
		real_abs(relCenter.z) - sphere.radius > box.halfSize.z)
	{
		return 0;
	}

	Vector3 closest_pt(0, 0, 0);
	real dist;
	// clamp to box
	dist = relCenter.x;
	if (dist > box.halfSize.x) dist = box.halfSize.x;
	if (dist < -box.halfSize.x) dist = -box.halfSize.x;
	closest_pt.x = dist;

	dist = relCenter.y;
	if (dist > box.halfSize.y) dist = box.halfSize.y;
	if (dist < -box.halfSize.y) dist = -box.halfSize.y;
	closest_pt.y = dist;

	dist = relCenter.z;
	if (dist > box.halfSize.z) dist = box.halfSize.z;
	if (dist < -box.halfSize.z) dist = -box.halfSize.z;
	closest_pt.z = dist;

	dist = (closest_pt - relCenter).squared_Magnitude();
	if (dist > sphere.radius * sphere.radius) return 0;
	// compile the contact
	Vector3 closest_pt_world = box.getTransform().transform(closest_pt);

	Contact* contact = data->contacts;
	contact->contactNormal = (center - closest_pt_world);
	contact->contactNormal.normalize();
	contact->contactPoint = closest_pt_world;
	contact->penetration = sphere.radius - real_sqrt(dist);

	contact->body[0] = box.body;
	contact->body[1] = sphere.body;
	contact->restitution = data->restitution;
	contact->friction = data->friction;

	data->addContacts(1);
	return 1;
	


}

unsigned CollisionDetector::boxAndPoint(
	const CollisionBox& box,
	const Vector3& point,
	CollisionData* data)
{

	Vector3 relative_point = box.getTransform().transformInverse(point);
	Vector3 normal;

	real min_depth = box.halfSize.x - real_abs(relative_point.x);
	if (min_depth < 0) return 0;
	normal = box.getAxis(0) * ((relative_point.x < 0) ? -1 : 1);

	real depth = box.halfSize.y - real_abs(relative_point.y);
	if (depth < 0) return 0;

	else if (depth < min_depth)
	{
		min_depth = depth;
		normal = box.getAxis(1) * ((relative_point.y < 0) ? -1 : 1);
	}

	depth = box.halfSize.z - real_abs(relative_point.z);
	if (depth < 0) return 0;
	else if (depth < min_depth)
	{
		min_depth = depth;
		normal = box.getAxis(2) * ((relative_point.z < 0) ? -1 : 1);

	}

	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->body[0] = box.body;
	contact->body[1] = NULL;
	contact->penetration = min_depth;
	contact->contactPoint = point;
	contact->restitution = data->restitution;
	contact->friction = data->friction;
	data->addContacts(1);
	return 1;

}


real CollisionDetector::penetrationOnAxis(
	const CollisionBox& one,
	const CollisionBox& two,
	const Vector3& axis,
	const Vector3& tocenter
)
{
	real oneProj = one.projectToAxis(axis);
	real twoProj = two.projectToAxis(axis);

	real distance = real_abs(tocenter * axis);

	return oneProj + twoProj - distance;
}

bool CollisionDetector::tryAxis(
	const CollisionBox& one,
	const CollisionBox& two,
	Vector3 axis,
	const Vector3& tocenter,
	unsigned index,

	real& smallestPenetration,
	unsigned& smallestCase
)
{
	if (axis.squared_Magnitude() < 0.0001) return true;
	axis.normalize();

	real penetration = penetrationOnAxis(one, two, axis, tocenter);

	if (penetration < 0) return false;
	if (penetration < smallestPenetration)
	{
		smallestPenetration = penetration;
		smallestCase = index;
	}
	return true;
}




Vector3 CollisionDetector::find_point_of_contact(
	const Vector3& pOne,
	const Vector3& dOne,
	real oneSize,
	const Vector3& pTwo,
	const Vector3& dTwo,
	real twoSize,
	bool useOne)
{
	Vector3 toSt, cOne, cTwo;
	real dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	real denom, mua, mub;

	smOne = dOne.squared_Magnitude();
	smTwo = dTwo.squared_Magnitude();
	dpOneTwo = dTwo * dOne;

	toSt = pOne - pTwo;
	dpStaOne = dOne * toSt;
	dpStaTwo = dTwo * toSt;

	denom = smOne * smTwo - dpOneTwo * dpOneTwo;

	// parallel lines
	if (real_abs(denom) < 0.0001f) {
		return useOne ? pOne : pTwo;
	}

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

	// If either of the edges has the nearest point out
	// of bounds, then the edges aren't crossed, we have
	// an edge-face contact. Our point is on the edge, which
	// we know from the useOne parameter.
	if (mua > oneSize ||
		mua < -oneSize ||
		mub > twoSize ||
		mub < -twoSize)
	{
		return useOne ? pOne : pTwo;
	}

	else
	{
		cOne = pOne + dOne * mua;
		cTwo = pTwo + dTwo * mub;

		return cOne * 0.5 + cTwo * 0.5;
	}

}

void CollisionDetector::generate_Point_Face_Contact(
	const CollisionBox& one,
	const CollisionBox& two,
	const Vector3& toCenter,
	CollisionData* data,
	unsigned best,
	real pen
)
{

	Contact* contact = data->contacts;

	Vector3 normal = one.getAxis(best);
	if (one.getAxis(best) * toCenter > 0)
	{
		normal = normal * -1.0f;
	}

	//Calculate which vertex of box two the collision happens with
	Vector3 vertex = two.halfSize;
	if (two.getAxis(0) * normal < 0) vertex.x = -vertex.x;
	if (two.getAxis(1) * normal < 0) vertex.y = -vertex.y;
	if (two.getAxis(2) * normal < 0) vertex.z = -vertex.z;

	contact->contactNormal = normal;
	contact->penetration = pen;
	contact->contactPoint = two.getTransform() * vertex;
	contact->body[0] = one.body;
	contact->body[1] = two.body;
	contact->friction = data->friction;
	contact->restitution = data->restitution;


}

unsigned CollisionDetector::boxAndBox(
	const CollisionBox& one,
	const CollisionBox& two,
	CollisionData* data
)
{

}


