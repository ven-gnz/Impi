#pragma once

#include <physics/Objects/Firework.h>
#include <math/random.h>
namespace Impi
{



class FireworkSystem
{
public:


	void init(unsigned maxFireworks);

	void update(real dt);

	void initRules();

	std::vector<Firework>& getFireworks();
	/** Dispatches the given number of fireworks from the given parent. */
	void create(unsigned type, unsigned count, const Firework* parent);
	/** Dispatches a firework from the origin. */
	void create(unsigned type, const Firework* parent = NULL);

private:
	
	std::vector<Firework> fireworks{};
	std::vector<FireworkRule> rules{};

	unsigned nextFirework = 0;
	Random random;

	unsigned maxFireworks = 4096;
	
	

	
};

}
