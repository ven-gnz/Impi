#pragma once

#include "Vector3.h"

using namespace Impi;

class Particle
{


	Vector3 position;

	Vector3 velocity;

	Vector3 acceleration;

	Vector3 accumulatedForce;

	real damping;

	real inverseMass;

public:

	void integrate(real duration);
};