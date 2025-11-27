#pragma once
#include "RigidBody.h"
#include "ContactResolver.h"
#include "math/Matrix.h"

namespace Impi
{

	class Contact
	{

		friend class ContactResolver;

	public:
		RigidBody* body[2];

		
		Vector3 contactPoint;
		Vector3 contactNormal;
		real friction;
		real restitution;
		real penetration;

		void setBodyData(RigidBody* one, RigidBody* two,
			real f, real r)
		{
			body[0] = one;
			body[1] = two;
			friction = f;
			restitution = r;
		}
	protected:

		Matrix3 contactToWorldSpace;
		Vector3 contactVelocity;
		real desiredDeltaVelocity;
		Vector3 relativeContactPosition[2];

		void calculateContactBasis();

		void applyImpulse(const Vector3 &impulse,);
		
	};
};