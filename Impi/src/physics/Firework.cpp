#include <physics/Particle.h>
#include <assert.h>
#include <vector>

using namespace Impi;
class Firework : public Particle
{
public:

	real age;
	unsigned type;

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


	
	

	void create(Firework& firework, const Firework* parent = nullptr) const
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

		// Vector3 velocity = random vector(minVelocity, maxVelocity);
		//if (parent) velocity += parent->getVelocity();
		//firework.setVelocity(velocity);

		//firework.setMass(1);
		//firework.setDamping(damping);
		//firework.setAcceleration(gravity);
		//firework.clearAccumulator();

	};
};



