#pragma once
#include "Particle.h"

class ParticleWorld

{

	
	struct ParticleRegistration
	{
		Particle* particle;
		ParticleRegistration* next;
	};
	void startFrame();

};