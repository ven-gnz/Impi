#include "src/physics/ParticleForceGenerators.h"

void ParticleGravity::updateForce(Particle* particle, real duration)
{
	if (!particle->hasFiniteMass()) return;

	particle->addForce(gravity * particle->getMass());
}

void ParticleDrag::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getVelocity();

	real dragCoeff = force.magnitude();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	force.normalize();
	force *= -dragCoeff;
	particle->addForce(force);


}