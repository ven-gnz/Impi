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


class ParticleSpring : public ParticleForceGenerator
{
	Particle* other;
	real springConstant;
	real restLength;

public:
	ParticleSpring(Particle* other, real springConstant, real restLength);
	virtual void updateForce(Particle* particle, real duration);
};



class ParticleAnchoredSpring : public ParticleForceGenerator
{
	Vector3* anchor;
	real springConstant;
	real restLength;

public:

	ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength);
	virtual void updateForce(Particle* particle, real duration);
};

class ParticleBungee : public ParticleForceGenerator
{
	Particle* other;
	real springConstant;
	real restLength;

public:

	ParticleBungee(Particle* other, real springConstant, real restLength);
	virtual void updateForce(Particle* particle, real duration);
};

class ParticleBuoyancy : public ParticleForceGenerator
{
	real maxDepth;
	real volume;
	real waterHeight;
	real liquidDensity;

public:

	ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity);
	virtual void updateForce(Particle* particle, real duration);
};

class ParticleFakeSpring : public ParticleForceGenerator
{
	Vector3* anchor;
	real springConstant;
	real damping;

public:
	ParticleFakeSpring(Vector3* anchor, real springConstant, real damping);
	virtual void updateForce(Particle* particle, real duration);
};
