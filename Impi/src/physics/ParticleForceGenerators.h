#pragma once
#include "src/physics/Particle.h"
using namespace Impi;

class ParticleForceGenerator
{
public:

	virtual void updateForce(Particle* particle, real duration) = 0;
};