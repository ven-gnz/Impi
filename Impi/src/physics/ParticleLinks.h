#pragma once
#include "Particle.h"
#include "ParticleContacts.h"

class ParticleLink
{
public :

	Particle* particle[2];

protected:

	real currentLength() const;

public:
	virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const = 0;


};

/**
 * Cables link a pair of particles, generating a contact if they
 * stray too far apart.
 */
class ParticleCable : public ParticleLink
{
public:
	
	real maxLength;

	/**
	* Bounciness of the cable
	*/
	real restitution;

	virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;
};


/**
* Rods link a pair of particles, generating a contact if they
* stray too far apart or too close.
*/
class ParticleRod : public ParticleLink
{

public:

	real length;

public:
	real currentLength() const;

	virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;
};