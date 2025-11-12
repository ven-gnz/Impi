#pragma once
#include "RigidBody.h"

namespace Impi
{
	class ForceGenerator
	{
	public:

		virtual void updateForce(RigidBody* body, real duration) = 0;
	};

	class Gravity : public ForceGenerator
	{
		Vector3 gravity;

	public:

		Gravity();
		Gravity(const Vector3& gravity);
		virtual void updateForce(RigidBody* body, real duration);
	};

	class TorqueGenerator : public ForceGenerator
	{
		Vector3 torque;

	public:
		TorqueGenerator();

		void setTorque(const Vector3& torque);

		virtual void updateForce(RigidBody* body, real duration);
	};


	class Spring : public ForceGenerator
	{
		Vector3 connectionPoint;
		RigidBody* other;
		Vector3 otherConnectionPoint;
		real springConstant;
		real restLength;

	public:
		Spring();

		Spring(const Vector3& localConnectionPt,
			RigidBody* other,
			const Vector3& otherConnectionPoint,
			real springConstant,
			real restLength);

			virtual void updateForce(RigidBody* body, real duration);
	};
}