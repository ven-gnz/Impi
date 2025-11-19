#pragma once
#include "RigidBody.h"

namespace Impi
{

	class Contact
	{

	public:
		RigidBody* body[2];

		
		Vector3 contactPoint;
		Vector3 contactNormal;
		real penetration;
	};
};