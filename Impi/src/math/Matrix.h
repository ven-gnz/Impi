#pragma once
#include "Precision.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <array>

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

		/**
		* Cosntructor for building a 3x3 matrix. Each vector corresponds to a column.
		*/
		Matrix3(const Vector3& compOne, const Vector3& compTwo,
			const Vector3& compThree);

		void setComponents(const Vector3& compOne, const Vector3& compTwo,
			const Vector3& compThree);

		Matrix3(real c0, real c1, real c2, real c3, real c4, real c5,
			real c6, real c7, real c8);

		/**
		* Get the new multiplied matrix
		*/
		Matrix3 operator*(const Matrix3& o);


		void operator+=(const Matrix3& o);

		/** In place matrix multiply
		*/
		void operator*=(const Matrix3& o);

		Matrix3 inverse() const;

		void invert();
		/**
		* Sets the matrix to be the inverse of the given matrix.
		*
		* @param m The matrix to invert and use to set this.
		*/
		void setInverse(const Matrix3& m);

		void setTranspose(const Matrix3& m);
		Matrix3 transpose() const;

		void setOrientation(const Quaternion& q);

		Vector3 transform(const Vector3& vector) const;
		Vector3 operator*(const Vector3& vector) const;

		static Matrix3 identity();
	};

/**
  * Holds a transform matrix, consisting of a rotation matrix and
  * a position. The matrix has 12 elements, it is assumed that the
  * remaining four are (0,0,0,1); producing a homogenous matrix.
  */
class Matrix4
{
public:

	real data[12];


	void setDiagonal(real a, real b, real c);

	

	/** Identity matrix as default constructor
	*/
	Matrix4();

	Matrix4 operator*(const Matrix4& o) const;

	Vector3 operator*(const Vector3& vector) const;

	Vector3 transform(const Vector3& vector) const;

	real getDeterminant() const;

	
	void setInverse(const Matrix4& m);

	Vector3 transformInverse(const Vector3& vector) const;

	Vector3 transformDirection(const Vector3& vector) const;

	Matrix4 inverse() const;

	void invert();
	

	void fillGLArray(float array[16]) const;

	std::array<float, 16> getGLarray();

	void setOrientationAndPos(const Quaternion& q, const Vector3& pos);

	Vector3 localToWorldDirection(const Vector3& local, const Matrix4& transform);
	Vector3 worldToLocalDirection(const Vector3& world, const Matrix4& transform);

	Vector3 getAxisVector(int i) const;




};

}                                                                                                
   
