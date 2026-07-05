#include "ParticleContacts.h"

void ParticleContact::resolve(real duration)
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
}

real ParticleContact::calculateSeparatingVelocity() const
{
	Vector3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1])
		{
		relativeVelocity -= particle[1]->getVelocity();
		}
	return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(real duration)
{

	real separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity > 0)
	{
		return;
	}

	real newSepVelocity = -separatingVelocity * restitution;

	Vector3 accCausedVelocity = particle[0]->getAcceleration();
	if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();

	real accCausedSepVelocity = accCausedVelocity * contactNormal * duration;

	if (accCausedSepVelocity < 0) {

		newSepVelocity += restitution * accCausedSepVelocity;

		if (newSepVelocity < 0) newSepVelocity = 0;
	}




	real deltaVelocity = newSepVelocity - separatingVelocity;

	real totalInverseMass = particle[0]->getMass();
	if (particle[1]) totalInverseMass += particle[1]->getMass();

	if (totalInverseMass <= 0) return;

	real impulse = deltaVelocity / totalInverseMass;

	Vector3 impulsePerIMass = contactNormal * impulse;

	particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * particle[0]->getMass());

	if (particle[1])
	{
		particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getMass());
	}
}

void ParticleContact::resolveInterpenetration(real duration)
{

	if (penetration <= 0) return;

	real totalInverseMass = particle[0]->getMass();
	if (particle[1]) totalInverseMass += particle[1]->getMass();

	if (totalInverseMass <= 0) return;

	Vector3 movePerIMass = contactNormal * (-penetration / totalInverseMass);

	particle[0]->setPosition(particle[0]->getPosition() + movePerIMass * particle[0]->getMass());

	if (particle[1])
	{
		particle[1]->setPosition(particle[1]->getPosition() + movePerIMass * particle[1]->getMass());
	}
}

ParticleContactResolver::ParticleContactResolver(unsigned iter)
{
	iterations = iter;
	iterationsUsed = 0;
}

void ParticleContactResolver::setIterations(unsigned iterations)
{
	iterations = iterations;
}

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned numContacts, real duration)
{
	iterationsUsed = 0;

	while (iterationsUsed < iterations)
	{
		real max = 0;
		unsigned maxIndex = numContacts;
		for (unsigned i = 0; i < numContacts; i++)
		{
			real separatingVelocity = contactArray[i].calculateSeparatingVelocity();

			if (separatingVelocity < max)
			{
				max = separatingVelocity;
				maxIndex = i;
			}
		}
		contactArray[maxIndex].resolve(duration);
		iterationsUsed++;
	}
	
}