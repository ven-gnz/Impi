#include "ForceRegistry.h"

using namespace Impi;

void ForceRegistry::updateForces(real duration)
{
	Registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
		i->fg->updateForce(i->body, duration);
	}
}

void ForceRegistry::add(RigidBody* body, ForceGenerator* fg)
{
	// Wrap to the desired struct for nicer iter
	ForceRegistry::ForceRegistration reg;
	reg.body = body;
	reg.fg = fg;
	registrations.push_back(reg);
}