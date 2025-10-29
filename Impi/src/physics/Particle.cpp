#include <physics/Particle.h>
#include <assert.h>

using namespace Impi;

Particle::Particle(const Vector3& pos, real mass, const Vector3& vel, real dam)
	: position(pos), inverseMass(mass), velocity(vel), damping(dam)
{ }

Particle::Particle()
	: position(Vector3(0, 0, 0)),
	inverseMass(1.0f),
	velocity(Vector3(0, 0, 0)),
	damping(1.0f)
{}

void Particle::integrate(real duration)
{
	assert(duration > 0.0);

	position.addScaledVector(velocity, duration);

	Vector3 resultingAcceleration = acceleration;
	resultingAcceleration.addScaledVector(accumulatedForce, inverseMass);
	velocity.addScaledVector(resultingAcceleration, duration);

	velocity *= real_pow(damping, duration);

	clearAccumulator();

}

void Particle::addForce(const Vector3& force)
{
	accumulatedForce += force;
}