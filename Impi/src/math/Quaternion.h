#pragma once
#include "Precision.h"
#include "Vector3.h"

namespace Impi {

	class Quaternion
	{
	public:
		union {
			struct
			{
				real r;
				real i;
				real j;
				real k;

			};
			real data[4];
		};
		
		Quaternion();
		Quaternion(const real r, const real i, const real j, const real k);
		void normalise();
		/**
		* Multiplies the quaternion by the given quaternion.
		*
		* @param multiplier The quaternion by which to multiply.
		*/
		void operator*=(const Quaternion& multiplier);
		void addScaledVector(const Vector3& vector, real scale);
		void rotateByVector(const Vector3& vector);


	};

}