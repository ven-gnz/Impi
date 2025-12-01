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

    if (body[1])
    {
        velocityFromAcc -= body[1]->getLastFrameAcceleration() * duration * contactNormal;
    }
	

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



void Contact::applyPositionChange(Vector3 linearChange[2],
    Vector3 angularChange[2],
    real penetration)
{
    const real angularLimit = (real)0.2f;
    real angularMove[2];
    real linearMove[2];

    real totalInertia = 0;
    real linearInertia[2];
    real angularInertia[2];

    // We need to work out the inertia of each object in the direction
    // of the contact normal, due to angular inertia only.
    for (unsigned i = 0; i < 2; i++) if (body[i])
    {
        Matrix3 inverseInertiaTensor;
        body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

        // Use the same procedure as for calculating frictionless
        // velocity change to work out the angular inertia.
        Vector3 angularInertiaWorld =
            relativeContactPosition[i].cross(contactNormal);
        angularInertiaWorld =
            inverseInertiaTensor.transform(angularInertiaWorld);
        angularInertiaWorld =
            angularInertiaWorld.cross(relativeContactPosition[i]);
        angularInertia[i] =
            angularInertiaWorld * contactNormal;

        // The linear component is simply the inverse mass
        linearInertia[i] = body[i]->getMass();

        // Keep track of the total inertia from all components
        totalInertia += linearInertia[i] + angularInertia[i];

        // We break the loop here so that the totalInertia value is
        // completely calculated (by both iterations) before
        // continuing.
    }

    // Loop through again calculating and applying the changes
    for (unsigned i = 0; i < 2; i++) if (body[i])
    {
        // The linear and angular movements required are in proportion to
        // the two inverse inertias.
        real sign = (i == 0) ? 1 : -1;
        angularMove[i] =
            sign * penetration * (angularInertia[i] / totalInertia);
        linearMove[i] =
            sign * penetration * (linearInertia[i] / totalInertia);

        // To avoid angular projections that are too great (when mass is large
        // but inertia tensor is small) limit the angular move.
        Vector3 projection = relativeContactPosition[i];
        projection.addScaledVector(
            contactNormal,
            -relativeContactPosition[i].scalarProduct(contactNormal)
        );

        // Use the small angle approximation for the sine of the angle (i.e.
        // the magnitude would be sine(angularLimit) * projection.magnitude
        // but we approximate sine(angularLimit) to angularLimit).
        real maxMagnitude = angularLimit * projection.magnitude();

        if (angularMove[i] < -maxMagnitude)
        {
            real totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = -maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }
        else if (angularMove[i] > maxMagnitude)
        {
            real totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }

        // We have the linear amount of movement required by turning
        // the rigid body (in angularMove[i]). We now need to
        // calculate the desired rotation to achieve that.
        if (angularMove[i] == 0)
        {
            // Easy case - no angular movement means no rotation.
            angularChange[i].clear();
        }
        else
        {
            // Work out the direction we'd like to rotate in.
            Vector3 targetAngularDirection =
                relativeContactPosition[i].cross(contactNormal);

            Matrix3 inverseInertiaTensor;
            body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

            // Work out the direction we'd need to rotate to achieve that
            angularChange[i] =
                inverseInertiaTensor.transform(targetAngularDirection) *
                (angularMove[i] / angularInertia[i]);
        }

        // Velocity change is easier - it is just the linear movement
        // along the contact normal.
        linearChange[i] = contactNormal * linearMove[i];

        // Now we can start to apply the values we've calculated.
        // Apply the linear movement
        Vector3 pos;
        body[i]->getPosition(&pos);
        pos.addScaledVector(contactNormal, linearMove[i]);
        body[i]->setPosition(pos);

        // And the change in orientation
        Quaternion q;
        body[i]->getOrientation(&q);
        q.addScaledVector(angularChange[i], ((real)1.0));
        body[i]->setOrientation(q);

        body[i]->calculateDerivedData();
    }
}



void Contact::applyVelocityChange(Vector3 velocityChange[2],
    Vector3 rotationChange[2])
{
    // Get hold of the inverse mass and inverse inertia tensor, both in
    // world coordinates.
    Matrix3 inverseInertiaTensor[2];
    body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
    if (body[1])
        body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

    // We will calculate the impulse for each contact axis
    Vector3 impulseContact;

    if (friction <= (real)0.01)
    {
        // Use the short format for frictionless contacts
        impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
        std::cout << "Calculated impulse without friction" << std::endl;
        std::cout << impulseContact << std::endl;
    }
    else
    {
        // Otherwise we may have impulses that aren't in the direction of the
        // contact, so we need the more complex version.
        impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
    }

    // Convert impulse to world coordinates
    Vector3 impulse = contactToWorldSpace.transform(impulseContact);
    std::cout << "Impulse in world coords: " << impulse << std::endl;

    // Split in the impulse into linear and rotational components
    Vector3 impulsiveTorque = relativeContactPosition[0].cross(impulse);
    rotationChange[0] = inverseInertiaTensor[0].transform(impulsiveTorque);
    velocityChange[0].clear();
    velocityChange[0].addScaledVector(impulse, body[0]->getMass());

    std::cout << "Body 0 linear velocity change: " << velocityChange[0]
        << ", angular change: " << rotationChange[0] << std::endl;

    // Apply the changes
    body[0]->addVelocity(velocityChange[0]);
    body[0]->addRotation(rotationChange[0]);

    if (body[1])
    {
        // Work out body one's linear and angular changes
        Vector3 impulsiveTorque = impulse.cross(relativeContactPosition[1]);
        rotationChange[1] = inverseInertiaTensor[1].transform(impulsiveTorque);
        velocityChange[1].clear();
        velocityChange[1].addScaledVector(impulse, -body[1]->getMass());

        // And apply them.
        body[1]->addVelocity(velocityChange[1]);
        body[1]->addRotation(rotationChange[1]);
    }
}

Vector3 Contact::calculateFrictionlessImpulse(Matrix3* inverseInertiaTensor)
{
    Vector3 impulseContact;

    // Build a vector that shows the change in velocity in
    // world space for a unit impulse in the direction of the contact
    // normal.
    Vector3 deltaVelWorld = relativeContactPosition[0].cross(contactNormal);
    deltaVelWorld = inverseInertiaTensor[0].transform(deltaVelWorld);
    deltaVelWorld = deltaVelWorld.cross(relativeContactPosition[0]);

    // Work out the change in velocity in contact coordiantes.
    real deltaVelocity = deltaVelWorld * contactNormal;

    // Add the linear component of velocity change
    deltaVelocity += body[0]->getMass();

    // Check if we need to the second body's data
    if (body[1])
    {
        // Go through the same transformation sequence again
        Vector3 deltaVelWorld = relativeContactPosition[1].cross(contactNormal);
        deltaVelWorld = inverseInertiaTensor[1].transform(deltaVelWorld);
        deltaVelWorld = deltaVelWorld.cross(relativeContactPosition[1]);

        // Add the change in velocity due to rotation
        deltaVelocity += deltaVelWorld * contactNormal;

        // Add the change in velocity due to linear motion
        deltaVelocity += body[1]->getMass();
    }

    // Calculate the required size of the impulse
    impulseContact.x = desiredDeltaVelocity / deltaVelocity;
    impulseContact.y = 0;
    impulseContact.z = 0;
    return impulseContact;
}

Vector3 Contact::calculateFrictionImpulse(Matrix3* inverseInertiaTensor)
{
    return Vector3(0, 0, 0);
}