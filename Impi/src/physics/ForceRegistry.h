#pragma once

#include "ForceGenerators.h"
#include "RigidBody.h"
#include <vector>

namespace Impi

{


class ForceRegistry

{

	struct ForceRegistration
	{
		RigidBody* body;
		ForceGenerator* fg;
	};

	typedef std::vector<ForceRegistration> Registry;
	Registry registrations;

public:

	void add(RigidBody* body, ForceGenerator* fg);

	void remove(RigidBody* body, ForceGenerator* fg);

	void clear();

	void updateForces(real duration);

};

}
