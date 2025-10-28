#include "src/physics/ParticleForceRegistry.h"
#include "ParticleForceGenerators.h"
#include <algorithm>

void ParticleForceRegistry::updateForces(real duration)
{
    Registry::iterator i = registrations.begin();
    for (; i != registrations.end(); i++)
    {
        i->fg->updateForce(i->particle, duration);
    }
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
    ParticleForceRegistry::ParticleForceRegistration registration;
    registration.particle = particle;
    registration.fg = fg;
    registrations.push_back(registration);
}

void ParticleForceRegistry::clear()
{
    registrations.clear();
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{

    // https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    ParticleForceRegistration reg { particle, fg };
    
    registrations.erase(
        std::remove(registrations.begin(), registrations.end(), reg), registrations.end()
    );
}