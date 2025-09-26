#pragma once

#include "Vector3.h"

using namespace Impi;

class Particle
{
public:

	Vector3 position;

	Vector3 velocity;

	Vector3 acceleration;

	real damping;

	real inverseMass;
};