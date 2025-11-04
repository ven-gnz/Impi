#pragma once
#include "Particle.h"
#include "ParticleContacts.h"
#include "ParticleForceRegistry.h"
#include "ParticleForceGenerators.h"

#include <vector>


/**
* We keep up with the book in order not to encounter something unlikely in the future, or to make our own
* versions of the aggregate demos in the future.
*/
namespace Impi {

	struct ParticleRegistration {
		Particle* particle;
		ParticleRegistration* next;
	};

	class ParticleWorld

	{
	public:
		typedef std::vector<Particle*> Particles;
		typedef std::vector<ParticleContactGenerator*> ContactGenerators;

	protected:

		Particles particles;
		bool calculateIterations;

		ParticleForceRegistry registry;

		ParticleContactResolver resolver;
		ContactGenerators contactGenerators;

		ParticleContact* contacts;
		unsigned maxContacts;

		ParticleRegistration* firstParticle;

		void startFrame();

	public:
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0);

		unsigned generateContacts();

		void integrate(real duration);

		void runPhysics(real duration);

		void startFrame();

		Particles& getParticles();

		ContactGenerators& getContactGenerators();

		ParticleForceRegistry& getForceRegistry();


		void runPhysics(real duration);
	};

	class GroundContacts : public Impi::ParticleContactGenerator
	{
		Impi::ParticleWorld::Particles* particles;

	public:
		void init(Impi::ParticleWorld::Particles* particles);

		virtual unsigned addContact(Impi::ParticleContact* contact,
			unsigned limit) const;
	};

}