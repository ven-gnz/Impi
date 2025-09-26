#pragma once

#include "precision.h"

namespace Impi
{
	class Vector3
	{
	private:
		real pad;

	public:

		real x, y, z;

		Vector3(const real x, const real y, const real z);
		Vector3();

		void operator-=(const Vector3& v);
		void operator*=(const real value);
		void operator+=(const Vector3& v);

		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(const real value) const;
		Vector3 operator+(const Vector3& v) const;

		void addScaledVector(const Vector3& v, real scale);
		void componentProductUpdate(const Vector3& vec);

		Vector3 componentProduct(const Vector3& vec) const;
		real scalarProduct(const Vector3& vector) const;
		real operator*(const Vector3& vector) const;

		Vector3 cross(const Vector3& vector) const;
		void operator %=(const Vector3& vector);

		void invert();
		real magnitude() const;
		real squared_Magnitude() const;
		void normalize();

	};

}

