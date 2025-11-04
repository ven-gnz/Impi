#pragma once
#include "src/physics/ParticleForceGenerators.h"
#include "src/physics/Particle.h"
#include <vector>

class ParticleForceRegistry
{
public:

	struct ParticleForceRegistration
	{
		Particle* particle;
		ParticleForceGenerator* fg;
		/*
		Own addition for remove (heh).
		*/
		bool operator==(const ParticleForceRegistration& other) const
		{
			return particle == other.particle && fg == other.fg;
		}
	};

	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

public:

	void add(Particle* particle, ParticleForceGenerator* fg);
	void remove(Particle* particle, ParticleForceGenerator* fg);
	void clear();
	void updateForces(real duration);

	
	
};

