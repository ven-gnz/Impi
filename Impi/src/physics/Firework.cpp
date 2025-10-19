#include <physics/Particle.h>
#include <assert.h>


using namespace Impi;
class Firework : public Particle
{
public:

	real age;

	bool update(real duration)
	{
		integrate(duration);

		age -= duration;
		return (age < 0);
	}
	
};