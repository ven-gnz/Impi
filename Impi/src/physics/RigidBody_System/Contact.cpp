#include "Contact.h"
#include <assert.h>

using namespace Impi;

void Contact::calculateContactBasis()
{

	Vector3 contactTangent[2];

	
	if (real_abs(contactNormal.x) > real_abs(contactNormal.y))
	{
		const real s = (real)1.0f /
			real_sqrt(
				contactNormal.z * contactNormal.z +
				contactNormal.x * contactNormal.x);

		// The new X-axis is at right angles to the world Y-axis
		contactTangent[0].x = contactNormal.z * s;
		contactTangent[0].y = 0;
		contactTangent[0].z = -contactNormal.x * s;

		contactTangent[1].x = contactNormal.y * contactTangent[0].x;
		contactTangent[1].y = contactNormal.z*contactTangent[0].x 
			- contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
	}
	else
	{
		const real s = (real)1.0f /
			real_sqrt(
				contactNormal.z * contactNormal.z +
				contactNormal.x * contactNormal.x);

		// The new X-axis is at right angles to the world X-axis
		contactTangent[0].x = 0;
		contactTangent[0].y = -contactNormal.z * s;
		contactTangent[0].z = contactNormal.y * s;

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].x = contactNormal.y * contactTangent[0].z -
			contactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = contactNormal.x * contactTangent[0].y;

	}

	contactToWorldSpace.setComponents(
		contactNormal,
		contactTangent[0],
		contactTangent[1]
	);



}

void Contact::swapBodies()
{
	contactNormal *= -1;

	RigidBody* temp = body[0];
	body[0] = body[1];
	body[1] = temp;
}


Vector3 Contact::calculateLocalVelocity(unsigned bodyIndex, real duration)
{
	RigidBody* thisbody = body[bodyIndex];

	Vector3 velocity = thisbody->getRotation().cross(relativeContactPosition[bodyIndex]);
	velocity += thisbody->getVelocity();

	Vector3 contactVelocity = contactToWorldSpace.transformTranspose(velocity);

	Vector3 accVelocity = thisbody->getLastFrameAcceleration() * duration;

	accVelocity = contactToWorldSpace.transformTranspose(accVelocity);

	accVelocity.x = 0;
	contactVelocity += accVelocity;

	return contactVelocity;
}

void Contact::calculateDesiredDeltaVelocity(real duration)
{

	const static real velocityLimit = (real)0.25f;
	real velocityFromAcc = 0;

	velocityFromAcc += body[0]->getLastFrameAcceleration() * duration * contactNormal;

	velocityFromAcc -= body[1]->getLastFrameAcceleration() * duration * contactNormal;

	real thisRestitution = restitution;

	if (real_abs(contactVelocity.x) < velocityLimit)
	{
		thisRestitution = (real)0.0f;
	}

	desiredDeltaVelocity =
		-contactVelocity.x
		- thisRestitution * (contactVelocity.x - velocityFromAcc);

}


void Contact::calculateInternals(real duration)
{
	if (!body[0]) swapBodies();
	assert(body[0]);
	
	calculateContactBasis();

	relativeContactPosition[0] = contactPoint - body[0]->getPosition();
	if (body[1])
	{
		relativeContactPosition[1] = contactPoint - body[1]->getPosition();
	}

	contactVelocity = calculateLocalVelocity(0, duration);
	if (body[1]) {
		contactVelocity -= calculateLocalVelocity(1, duration);
	}
	calculateDesiredDeltaVelocity(duration);
}