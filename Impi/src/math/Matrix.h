#pragma once
#include "Precision.h"
#include "Vector3.h"

namespace Impi
{



	/**
	* Holds an inertia tensor, consisting of a 3x3 row-major matrix.
	* The matrix is not padding to produce an aligned structure, since it is most commmonly used with a mass
	* and two damping coefficitens to make the 12-element characteristic array of a rigid body.
	*/
	class Matrix3
	{
	public:

		real data[9];

		Matrix3();

		Matrix3(real c0, real c1, real c2, real c3, real c4, real c5,
			real c6, real c7, real c8);

		Matrix3 operator*(const Matrix3& o)
		{
			return Matrix3
			(	data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
				data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
				data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],
				data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
				data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
				data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],
				data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
				data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
				data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
			);
		}
	};


class Matrix4
{
public:

	real data[12];



	Vector3 operator*(const Vector3& vector) const
	{
		return Vector3(
			vector.x * data[0] +
			vector.y * data[1] +
			vector.z * data[2],
			vector.x * data[4] +
			vector.y * data[5] +
			vector.z * data[6],
			vector.x * data[8] +
			vector.y * data[9] +
			vector.y * data[10]);
	}

	Matrix4 operator*(const Matrix4& o) const
	{
		return Matrix4
		(
			data[0] * o.data[0] + data[1] * o.data[4] + data[2] * o.data[8], data[3] * o.data[12],
			data[0] * o.data[1] + data[1] * o.data[5] + data[2] * o.data[9], data[3] * o.data[13],
			data[0] * o.data[2] + data[1] * o.data[6] + data[2] * o.data[10], data[3] * o.data[14],
			data[0] * o.data[3] + data[1] * o.data[7] + data[2] * o.data[11], data[3] * o.data[15],
			data[4] * o.data[0] + data[5] * o.data[4] + data[6] * o.data[8], data[7] * o.data[12],
			data[4] * o.data[1] + data[5] * o.data[5] + data[6] * o.data[9], data[7] * o.data[13],
			data[4] * o.data[2] + data[5] * o.data[6] + data[6] * o.data[10], data[7] * o.data[14],
			data[4] * o.data[3] + data[5] * o.data[7] + data[6] * o.data[11], data[7] * o.data[15],
			data[8] * o.data[0] + data[9] * o.data[4] + data[10] * o.data[8], data[11] * o.data[12],
			data[8] * o.data[1] + data[9] * o.data[5] + data[10] * o.data[9], data[11] * o.data[13],
			data[8] * o.data[2] + data[9] * o.data[6] + data[10] * o.data[10], data[11] * o.data[14],
			data[8] * o.data[3] + data[9] * o.data[7] + data[10] * o.data[11], data[11] * o.data[15],
			data[12] * o.data[0] + data[13] * o.data[4] + data[14] * o.data[8], data[15] * o.data[12],
			data[12] * o.data[1] + data[13] * o.data[5] + data[14] * o.data[9], data[15] * o.data[13],
			data[12] * o.data[2] + data[13] * o.data[6] + data[14] * o.data[10], data[15] * o.data[14],
			data[12] * o.data[3] + data[13] * o.data[7] + data[14] * o.data[11], data[15] * o.data[15],
		);
	}
};

}                                                                                                
   
