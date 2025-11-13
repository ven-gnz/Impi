#include "Vector3.h"

using namespace Impi;


		Vector3::Vector3() : x(0), y(0), z(0), pad(0) {}

		Vector3::Vector3(const real x,
						const real y,
						const real z) : x(x), y(y), z(z), pad(0) { }

	
	
			void Vector3::operator*=(const real value)
			{
				x *= value;
				y *= value;
				z *= value;
			}

			void Vector3::operator+=(const Vector3& v)
				{
					x += v.x;
					y += v.y;
					z += v.z;
				}

			void Vector3::operator-=(const Vector3& v)
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
				}

			void Vector3::addScaledVector(const Vector3& v, real scale)
			{
				x += v.x * scale;
				y += v.y * scale;
				z += v.z * scale;
			}

			void Vector3::componentProductUpdate(const Vector3& vec)
			{
				x *= vec.x;
				y *= vec.y;
				z *= vec.z;
			}


			Vector3 Vector3::operator+(const Vector3& v) const
			{
				return Vector3(x + v.x, y + v.y, z + v.z);
			}

			Vector3 Vector3::operator*(const real value) const
			{
				return Vector3(x * value, y * value, z * value);
			}

			Vector3 Vector3::operator-(const Vector3& v) const
			{
				return Vector3(x - v.x, y - v.y, z - v.z);
			}

		
			Vector3 Vector3::componentProduct(const Vector3& vec) const
			{
				return Vector3(x * vec.x, y * vec.y, z * vec.z);
			}

			real Vector3::dot(const Vector3& vector) const
			{
				return x * vector.x + y * vector.y + z * vector.z;
			}

			real Vector3::operator*(const Vector3& vector) const
			{
				return x * vector.x + y * vector.y + z * vector.z;
			}

			Vector3 Vector3::cross(const Vector3& vector) const
			{
				return Vector3(y * vector.z - z * vector.y,
					z * vector.x - x * vector.z,
					x * vector.y - y * vector.x);
			}

			void Vector3::operator %=(const Vector3 &vector)
			{
				*this = cross(vector);
			}
			

			void Vector3::invert()
			{
				x = -x;
				y = -y;
				z = -z;
			}

			real Vector3::magnitude() const
			{
				return real_sqrt(x * x + y * y + z * z);
			}

			real Vector3::squared_Magnitude() const
			{
				return real(x * x + y * y + z * z);
			}


			void Vector3::normalize()
			{
				real l = magnitude();
				if (l > 0)
				{
					(*this) *= ((real)1) / l;
				}
			}

			Vector3 Vector3::normalized()
			{
				float l = magnitude();
				if (l > 0.0f)
				{
					return *this * (1/l);
				}
				return Vector3(0, 0, 0);
			}

	
		