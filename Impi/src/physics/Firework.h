#pragma once
#include <physics/Particle.h>
#include <assert.h>
#include <vector>
#include <src/math/random.h>

class Firework : public Particle
{
public:
    real age;
    unsigned type;
	Random simplerandom = Random();

	bool update(real duration);
};

struct FireworkRule
{
    struct Payload
    {
        unsigned type = 0;
        unsigned count = 0;
    };

    unsigned type = 0;
    real minAge = 0;
    real maxAge = 0;
    Vector3 minVelocity;
    Vector3 maxVelocity;
    real damping = 1.0;
    std::vector<Payload> payloads;

    void create(Firework& firework,
        const Firework* parent,
        Random& ran) const;


};