#include "src/physics/Particle_System/ParticleForceGenerators.h"

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

ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity)
	: maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity) { }

void ParticleBuoyancy::updateForce(Particle* particle, real duration)
{
	real depth = particle->getPosition().y;

	if (depth >= waterHeight + maxDepth) return;
	Vector3 force(0, 0, 0);

	// in too deep
	if (depth <= waterHeight - maxDepth)
	{
		force.y = liquidDensity * volume;
		particle->addForce(force);
		return;
	}
	// partial submersion
	else
	{
		force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
		particle->addForce(force);
	}
}

ParticleFakeSpring::ParticleFakeSpring(Vector3* anchor, real springConstant, real damping)
	:anchor(anchor), springConstant(springConstant), damping(damping) {}

void ParticleFakeSpring::updateForce(Particle* particle, real duration)
{
	if (!particle->hasFiniteMass()) return;
	Vector3 position = particle->getPosition();
	position -= *anchor;

	// Calculate the constants and check whether they are in bounds.
	real gamma = 0.5f * real_sqrt(4 * springConstant - damping * damping);
	if (gamma == 0.0f) return;
	Vector3 c = position * (damping / (2.0f * gamma)) + particle->getVelocity() * (1.0f / gamma);


	Vector3 target = position * real_cos(gamma * duration) + c * real_sin(gamma * duration);

	target *= real_exp(-0.5f * duration * damping);
	
	Vector3 acceleration = (target - position) * (1.0f / duration * duration) - particle->getVelocity() * duration;
	particle->addForce(acceleration * particle->getMass());

}