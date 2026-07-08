#include <physics/Objects/FireworkSystem.h>
#include <iostream>

using namespace Impi;

void FireworkSystem::init(unsigned maxFireworks)
{
	fireworks.resize(maxFireworks);

	random = Random();

	initRules();
}

void FireworkSystem::update(real dt)
{
   
    if (dt <= 0.0f) return;
    // changed this to be closer to original demo to rule out a suspect in bug hunt.
    for (size_t i = 0; i < fireworks.size(); ++i)
    {

        Firework& firework = fireworks[i];
        if (firework.type == 0) continue;

        bool expired = firework.update(dt);

        if (expired)
        {
            FireworkRule& rule = rules[firework.type - 1];
            firework.type = 0;

            for (const auto& payload : rule.payloads)
            {
                create(payload.type, payload.count, &firework);
            }
        }
    }
}

void FireworkSystem::create(unsigned type, unsigned count, const Firework* parent)
{
    std::cout << "firework system creating" << std::endl;
    for (unsigned i = 0; i < count; i++)
    {
        Firework& firework = fireworks[nextFirework];
        FireworkRule& rule = rules[type - 1];
        //delegate further
        rule.create(firework, parent, random);

        nextFirework = (nextFirework + 1) % fireworks.size();
    }
}


void FireworkSystem::create(unsigned type, const Firework* parent)
{
    std::cout << "firework system creating" << std::endl;
    create(type, 1, parent);
}




void FireworkSystem::initRules()
{
    rules.push_back(
        FireworkRule
        {
        1, // type
        0.5f, 1.4f, // age range
        Vector3(-5, 15, -5), // min velocity
        Vector3(5, 20, 5), // max velocity
        0.1, // damping
        {{3,5 }, {5,5}} //payloads
        }
    );

    rules.push_back(
        FireworkRule
        {
        2, // type
        0.5f, 1.0f, // age range
        Vector3(-5, 8, -5), // min velocity
        Vector3(5, 16, 5), // max velocity
        0.8, // damping
        {{4,2}} //payloads
        }
    );

    rules.push_back(
        FireworkRule
        {
        3, // type
        0.5f, 1.5f, // age range
        Vector3(-5, -5, -5), // min velocity
        Vector3(5, 5, 5), // max velocity
        0.1 // damping
             //payloads
        }
    );

    rules.push_back(
        FireworkRule
        {
        4, // type
        0.25f, 0.5f, // age range
        Vector3(-20, 5, -5), // min velocity
        Vector3(20, 5, 5), // max velocity
        0.2 // damping
         //payloads
        }
    );


    rules.push_back(
        FireworkRule
        {
        5, // type
        0.5f, 1.0f, // age range
        Vector3(-20, 2, -5), // min velocity
        Vector3(20, 12, 5), // max velocity
        0.01, // damping
        {{3,5 }} //payloads
        }
    );


    rules.push_back(
        FireworkRule
        {
        6, // type
        2, 4, // age range
        Vector3(-5, 5, -5), // min velocity
        Vector3(5, 10, 5), // max velocity
        0.95, // damping
        //payloads
        }
        );


    rules.push_back(
        FireworkRule
        {
        7, // type
        2, 4, // age range
        Vector3(-5, 15, -5), // min velocity
        Vector3(5, 25, 5), // max velocity
        0.01, // damping
        {{8,10 }} //payloads
        }
    );


    rules.push_back(
        FireworkRule
        {
        8, // type
        0.25f, 0.5f, // age range
        Vector3(-1, -1, -1), // min velocity
        Vector3(1, 1, 1), // max velocity
        0.01 // damping
             //payloads
        }
    );


    rules.push_back(
        FireworkRule
        {
        9, // type
        2, 3, // age range
        Vector3(-15, 8, -5), // min velocity
        Vector3(15, 9, 5), // max velocity
        0.95 // damping
             //payloads
        }
    );

}

std::vector<Firework>& FireworkSystem::getFireworks() { return fireworks; }