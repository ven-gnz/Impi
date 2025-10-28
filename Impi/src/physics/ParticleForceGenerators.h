#pragma once
#include "src/physics/Particle.h"
using namespace Impi;

class ParticleForceGenerator
{
public:

	virtual void updateForce(Particle* particle, real duration) = 0;
};

class ParticleGravity : public ParticleForceGenerator
{
	Vector3 gravity;

public:
	ParticleGravity(const Vector3& gravity);
	virtual void updateForce(Particle* particle, real duration);
};

class ParticleDrag : public ParticleForceGenerator
{
	// velocity drag coefficient
	real k1;
	// velocity squared drag coefficient
	real k2;

public:
	ParticleDrag(real k1, real k2);
	virtual void updateForce(Particle* particle, real duration);
};