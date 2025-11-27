#pragma once
#include "RigidBody.h"
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

		Vector3 calculateLocalVelocity(unsigned bodyIndex, real duration);

		void calculateDesiredDeltaVelocity(real duration);
	protected:

		Matrix3 contactToWorldSpace;
		Vector3 contactVelocity;
		real desiredDeltaVelocity;
		Vector3 relativeContactPosition[2];

		void swapBodies();

		void calculateContactBasis();

		void calculateInternals(real duration);

		void applyVelocityChange(Vector3 velocityChange[2],
			Vector3 rotationChange[2]);

		void applyPositionChange(Vector3 linearChange[2],
			Vector3 angularChange[2],
			real penetration);



		Vector3 calculateFrictionlessImpulse(Matrix3* inverseInertiaTensor);
		Vector3 calculateFrictionImpulse(Matrix3* inverseInertiaTensor);

	};
}