#include "ContactResolver.h"

using namespace Impi;


void ContactResolver::prepareContacts(Contact* contacts, unsigned numContacts, real duration)
{

	Contact* lastContact = contacts + numContacts;
	for (Contact* contact = contacts; contact < lastContact; contact++)
	{
		contact->calculateInternals(duration);
	}
}



void ContactResolver::resolveContacts(Contact* contacts, unsigned numContacts, real duration)
{
    
	if (numContacts == 0) return;
	prepareContacts(contacts, numContacts, duration);
	adjustPositions(contacts, numContacts, duration);
	adjustVelocities(contacts, numContacts, duration);
}

void ContactResolver::adjustVelocities(Contact* c,
	unsigned numContacts,
	real duration)
{
    Vector3 velocityChange[2], rotationChange[2];
    Vector3 deltaVel;

    // trying debug stuff
    //rotationChange[0] = Vector3(0, 0, 0);
    //rotationChange[1] = Vector3(0, 0, 0);

    // iteratively handle impacts in order of severity.
    velocityIterationsUsed = 0;
    while (velocityIterationsUsed < velocityIterations)
    {
        // Find contact with maximum magnitude of probable velocity change.
        real max = velocityEpsilon;
        unsigned index = numContacts;
        for (unsigned i = 0; i < numContacts; i++)
        {
            if (c[i].desiredDeltaVelocity > max)
            {
                max = c[i].desiredDeltaVelocity;
                index = i;
            }
        }
        if (index == numContacts) break;


        // Do the resolution on the contact that came out top.
        c[index].applyVelocityChange(velocityChange, rotationChange);

        // With the change in velocity of the two bodies, the update of
        // contact velocities means that some of the relative closing
        // velocities need recomputing.
        for (unsigned i = 0; i < numContacts; i++)
        {
            // Check each body in the contact
            for (unsigned b = 0; b < 2; b++) if (c[i].body[b])
            {
                // Check for a match with each body in the newly
                // resolved contact
                for (unsigned d = 0; d < 2; d++)
                {
                    if (c[i].body[b] == c[index].body[d])
                    {
                        deltaVel = velocityChange[d] +
                            rotationChange[d].cross(
                                c[i].relativeContactPosition[b]);

                        // The sign of the change is negative if we're dealing
                        // with the second body in a contact.

                        //std::cout << "Contact normal: " << c[index].contactNormal << "\n";
                        //std::cout << "Penetration: " << c[index].penetration << "\n";
                        //std::cout << "Relative contact pos[0]: " << c[index].relativeContactPosition[0] << "\n";
                        //std::cout << "Body[0] inverse mass: " << c[index].body[0]->getMass() << "\n";
                        //std::cout << "Body[0] inertia world:\n" << c[index].body[0]->inverseInertiaTensorWorld << "\n";
                        c[i].contactVelocity +=
                            c[i].contactToWorldSpace.transformTranspose(deltaVel)
                            * (b ? -1 : 1);
                        c[i].calculateDesiredDeltaVelocity(duration);
                    }
                }
            }
        }
        velocityIterationsUsed++;
    }
}

void ContactResolver::adjustPositions(Contact* c,
	unsigned numContacts,
	real duration)
{
    unsigned i, index;
    Vector3 linearChange[2], angularChange[2];
    real max;
    Vector3 deltaPosition;

    // trying debug stuff
    //angularChange[0] = Vector3(0, 0, 0);
    //angularChange[1] = Vector3(0, 0, 0);

    // iteratively resolve interpenetrations in order of severity.
    positionIterationsUsed = 0;
    while (positionIterationsUsed < positionIterations)
    {
        // Find biggest penetration
        max = positionEpsilon;
        index = numContacts;
        for (i = 0; i < numContacts; i++)
        {
            if (c[i].penetration > max)
            {
                max = c[i].penetration;
                index = i;
            }
        }
        if (index == numContacts) break;

        // Resolve the penetration.
        c[index].applyPositionChange(
            linearChange,
            angularChange,
            max);

        // Again this action may have changed the penetration of other
        // bodies, so we update contacts.
        for (i = 0; i < numContacts; i++)
        {
            // Check each body in the contact
            for (unsigned b = 0; b < 2; b++) if (c[i].body[b])
            {
                // Check for a match with each body in the newly
                // resolved contact
                for (unsigned d = 0; d < 2; d++)
                {
                    if (c[i].body[b] == c[index].body[d])
                    {
                        deltaPosition = linearChange[d] +
                            angularChange[d].cross(
                                c[i].relativeContactPosition[b]);

                        // The sign of the change is positive if we're
                        // dealing with the second body in a contact
                        // and negative otherwise (because we're
                        // subtracting the resolution)..
                        c[i].penetration +=
                            deltaPosition*(c[i].contactNormal)
                            * (b ? 1 : -1);
                    }
                }
            }
        }
        positionIterationsUsed++;
    }
}

void ContactResolver::setIterations(unsigned velocityIterations,
    unsigned positionIterations)
{
    ContactResolver::velocityIterations = velocityIterations;
    ContactResolver::positionIterations = positionIterations;
}


void ContactResolver::setEpsilon(real velocityEpsilon,
    real positionEpsilon)
{
    ContactResolver::velocityEpsilon = velocityEpsilon;
    ContactResolver::positionEpsilon = positionEpsilon;
}

void ContactResolver::setIterations(unsigned iterations)
{
    setIterations(iterations, iterations);
}



ContactResolver::ContactResolver(unsigned iterations,
    real velocityEpsilon,
    real positionEpsilon)
{
    setIterations(iterations, iterations);
    setEpsilon(velocityEpsilon, positionEpsilon);
}