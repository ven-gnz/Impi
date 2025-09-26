#include "particle.h"
#include <assert.h>

using namespace Impi;

void Particle::integrate(real duration)
{
	assert(duration > 0.0);

	position.addScaledVector(velocity, duration);

	Vector3 resultingAcceleration = acceleration;
	resultingAcceleration.addScaledVector(accumulatedForce, inverseMass);

	velocity *= real_pow(damping, duration);

}