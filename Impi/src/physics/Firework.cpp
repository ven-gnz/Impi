#include <src/physics/Firework.h>



bool Firework::update(real duration)
{
	integrate(duration);
	age -= duration;
	return (age < 0) || (position.y < 0);
}

	void FireworkRule::create(Firework& firework, const Firework* parent, Random& ran) const
	{
		firework.type = type;
		firework.age = ran.randomReal(minAge,maxAge);

		if (parent)
		{
			firework.setPosition(parent->getPosition());
		}
		else
		{
			Vector3 start;
			int x = (int) ran.randomInt(3) -1;
			start.x = 5.0f * static_cast<real>(x);
			firework.setPosition(start);
		}

		Vector3 velocity = ran.randomVector3(minVelocity, maxVelocity);
		if (parent) velocity += parent->getVelocity();
		firework.setVelocity(velocity);

		firework.setInvMass(1);
		firework.setDamping(damping);
		Vector3 Gravity = Vector3(real(0.0), real(-9.8) , real(0.0));
		firework.setAcceleration(Gravity);
		firework.clearAccumulator();

	}




