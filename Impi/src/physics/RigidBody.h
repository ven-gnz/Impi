#pragma once
#include "Precision.h"
#include "src/math/Vector3.h"
#include "src/math/Quaternion.h"
#include "src/math/Matrix.h"

namespace Impi
{



	class RigidBody
	{

	public:

		real inverseMass;

		Vector3 position;

		Quaternion orientation;

		Vector3 velocity;

		Vector3 rotation;

		Matrix4 transformMatrix;

		void calculateDerivedData();


		Matrix3 inverseInertiaTensor;

		void setInertiaTensor();
	};

	

}