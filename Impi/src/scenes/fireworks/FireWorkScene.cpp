#include "FireWorkScene.h"

using namespace Impi;

FireWorkScene::FireWorkScene(Camera& camera)
{

}


void FireWorkScene::initFireWorkRules()
{
    std::vector<FireworkRule> rules;

    rules.push_back(
        FireworkRule
        {
        1, // type
        0.5f, 1.4f, // age range
        Vector3(-5, 25, -5), // min velocity
        Vector3(5, 28, 5), // max velocity
        0.1, // damping
        {{3,5 }, {5,5}} //payloads
        }
    );

    rules.push_back(
        FireworkRule
        {
        2, // type
        0.5f, 1.0f, // age range
        Vector3(-5, 10, -5), // min velocity
        Vector3(5, 20, 5), // max velocity
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
        Vector3(20, 18, 5), // max velocity
        0.01, // damping
        {{3,5 }} //payloads
        }
        );


    rules.push_back(
        FireworkRule
        {
        6, // type
        3, 5, // age range
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
        4, 5, // age range
        Vector3(-5, 50, -5), // min velocity
        Vector3(5, 60, 5), // max velocity
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
        3, 5, // age range
        Vector3(-15, 10, -5), // min velocity
        Vector3(15, 15, 5), // max velocity
        0.95 // damping
             //payloads
        }
        );



/*
* COPYRIGHT NOTICE:
This legacy excerpt copied from the original cyclone engine, I do not own the copyright for this.
It is included in the project because I wanted to keep a reference to the original values for comparison purposes.
The original source code is published under MIT- license, so I thought this would be fine.

    // Go through the firework types and create their rules.
    rules[0].init(2);
    rules[0].setParameters(
        1, // type
        0.5f, 1.4f, // age range
        Vector3(-5, 25, -5), // min velocity
        Vector3(5, 28, 5), // max velocity
        0.1 // damping
    );
    rules[0].payloads[0].set(3, 5);
    rules[0].payloads[1].set(5, 5);

    rules[1].init(1);
    rules[1].setParameters(
        2, // type
        0.5f, 1.0f, // age range
        Vector3(-5, 10, -5), // min velocity
        Vector3(5, 20, 5), // max velocity
        0.8 // damping
    );
    rules[1].payloads[0].set(4, 2);

    rules[2].init(0);
    rules[2].setParameters(
        3, // type
        0.5f, 1.5f, // age range
        Vector3(-5, -5, -5), // min velocity
        Vector3(5, 5, 5), // max velocity
        0.1 // damping
    );

    rules[3].init(0);
    rules[3].setParameters(
        4, // type
        0.25f, 0.5f, // age range
        Vector3(-20, 5, -5), // min velocity
        Vector3(20, 5, 5), // max velocity
        0.2 // damping
    );

    rules[4].init(1);
    rules[4].setParameters(
        5, // type
        0.5f, 1.0f, // age range
        Vector3(-20, 2, -5), // min velocity
        Vector3(20, 18, 5), // max velocity
        0.01 // damping
    );
    rules[4].payloads[0].set(3, 5);

    rules[5].init(0);
    rules[5].setParameters(
        6, // type
        3, 5, // age range
        Vector3(-5, 5, -5), // min velocity
        Vector3(5, 10, 5), // max velocity
        0.95 // damping
    );

    rules[6].init(1);
    rules[6].setParameters(
        7, // type
        4, 5, // age range
        Vector3(-5, 50, -5), // min velocity
        Vector3(5, 60, 5), // max velocity
        0.01 // damping
    );
    rules[6].payloads[0].set(8, 10);

    rules[7].init(0);
    rules[7].setParameters(
        8, // type
        0.25f, 0.5f, // age range
        Vector3(-1, -1, -1), // min velocity
        Vector3(1, 1, 1), // max velocity
        0.01 // damping
    );

    rules[8].payloads(0);
    rules[8].setParameters(
        9, // type
        3, 5, // age range
        Vector3(-15, 10, -5), // min velocity
        Vector3(15, 15, 5), // max velocity
        0.95 // damping
    );
    // ... and so on for other firework types ...

    */
}