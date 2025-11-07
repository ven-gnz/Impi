#pragma once
#include "Precision.h"
#include "src/math/Vector3.h"
#include "src/math/Quaternion.h"
#include "src/math/Matrix.h"

namespace Impi
{



	class RigidBody
	{

	protected:

		real inverseMass;

		real linearDamping;

		real angularDamping;

		Vector3 position;

		Quaternion orientation;

		Vector3 velocity;

		Vector3 rotation;

		Vector3 forceAccum;

		Vector3 torqueAccum;

		Matrix4 transformMatrix;

	public:

		void calculateDerivedData();

		Matrix3 inverseInertiaTensor;

		Matrix3 inverseInertiaTensorWorld;

		void setInertiaTensor(const Matrix3 &inertiatensor);

		void addForce(const Vector3& force);

		void addForce();

		void addTorque(const Vector3& torque);

		void clearAccumulators();

		/**
		* Adds a give force to a given point, both in world space.
		*/
		void addForceAtPoint(const Vector3& force, const Vector3& point);

	};

	

}