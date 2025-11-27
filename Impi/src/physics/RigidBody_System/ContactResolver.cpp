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

}

void ContactResolver::adjustPositions(Contact* c,
	unsigned numContacts,
	real duration)
{

}