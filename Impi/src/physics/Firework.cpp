#include <physics/Particle.h>
#include <assert.h>
#include <vector>
#include <src/math/random.h>

using namespace Impi;
class Firework : public Particle

	
{
public:

	real age;
	unsigned type;
	Random simplerandom = Random();

	bool update(real duration)
	{
		integrate(duration);

		age -= duration;
		return (age < 0) || (position.y < 0);
	}

};

struct FireworkRule
{

	struct Payload
	{
		unsigned type;
		unsigned count;

		void set(unsigned type, unsigned count)
		{
			Payload::type = type;
			Payload::count = count;
		}
	};

	unsigned type = 0;
	real minAge = 0;
	real maxAge = 0;
	Vector3 minVelocity;
	Vector3 maxVelocity;
	real damping = 1.0;
	std::vector<Payload> payloads;

	void create(Firework& firework, const Firework* parent = nullptr, Random& ran) const
	{
		firework.type = type;
		firework.age = 1.5f; // -> need randomized age

		if (parent)
		{
			firework.setPosition(parent->getPosition());
		}
		else
		{
			Vector3 start;
			int x = 0; // another randomization
			start.x = 5.0f * static_cast<real>(x);
			firework.setPosition(start);
		}

		Vector3 velocity = ran.randomVector3(minVelocity, maxVelocity);
		if (parent) velocity += parent->getVelocity();
		firework.setVelocity(velocity);

		firework.setInvMass(1);
		firework.setDamping(damping);
		firework.setAcceleration(Vector3(0.0, -9.8, 0.0));
		firework.clearAccumulator();

	};
};



