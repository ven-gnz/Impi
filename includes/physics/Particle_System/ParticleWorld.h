#pragma once
#include <physics/Particle_System/Particle.h>
#include <physics/Particle_System/ParticleContacts.h>
#include <physics/Particle_System/ParticleForceRegistry.h>
#include <physics/Particle_System/ParticleForceGenerators.h>

#include <vector>



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

	

	public:
		ParticleWorld(unsigned maxContacts, unsigned iterations = 0);

		unsigned generateContacts();

		void integrate(real duration);

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