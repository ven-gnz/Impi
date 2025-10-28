#include "src/physics/ParticleForceGenerators.h"

ParticleGravity::ParticleGravity(const Vector3& gravity)
	: gravity(gravity) {}

void ParticleGravity::updateForce(Particle* particle, real duration)
{
	if (!particle->hasFiniteMass()) return;

	particle->addForce(gravity * particle->getMass());
}

ParticleDrag::ParticleDrag(real k1, real k2)
	: k1(k1), k2(k2) {}

void ParticleDrag::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getVelocity();

	real dragCoeff = force.magnitude();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	force.normalize();
	force *= -dragCoeff;
	particle->addForce(force);

}

ParticleSpring::ParticleSpring(Particle* other, real sc, real rl)
	: other(other), springConstant(sc), restLength(rl) {}

void ParticleSpring::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getPosition();

	force -= other->getPosition();

	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	force.normalize();
	force *= magnitude;
	particle->addForce(force);
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength)
	: anchor(anchor) , springConstant(springConstant), restLength(restLength) { }

void ParticleAnchoredSpring::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getPosition();
	force -= *anchor;

	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	force.normalize();
	force *= -magnitude;
	particle->addForce(force);

}

ParticleBungee::ParticleBungee(Particle* other, real springConstant, real restLength)
	: other(other) , springConstant(springConstant) , restLength(restLength) { }

void ParticleBungee::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getPosition();
	force -= other->getPosition();

	real magnitude = force.magnitude();

	if (magnitude <= restLength) return;
	magnitude = springConstant * (magnitude - restLength);

	force.normalize();
	force *= -magnitude;
	particle->addForce(force);
}