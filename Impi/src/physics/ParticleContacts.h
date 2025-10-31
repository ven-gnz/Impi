#pragma once
#include "Particle.h"

class ParticleContactResolver;

class ParticleContact
{
	

public:

	Particle* particle[2];
	real restitution;
	Vector3 contactNormal;

	real penetration;

protected:

	void resolve(real duration);

	real calculateSeparatingVelocity() const;


private:

	void resolveVelocity(real duration);

	void resolveInterpenetration(real duration);
};