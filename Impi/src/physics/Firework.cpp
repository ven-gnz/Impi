#include <physics/Particle.h>
#include <assert.h>
#include <vector>

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

struct FireworkRule
{
	unsigned type = 0;
	real minAge = 0;
	real maxAge = 0;
	Vector3 minVelocity;
	Vector3 maxVelocity;
	real damping = 1.0;
	std::vector<Payload> payloads;


	

	void create(Firework& firework, const Firework* parent = nullptr) const
	{
		

	};
};



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
		return (age < 0);
	}
	
};