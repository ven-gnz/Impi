#include "precision.h"

namespace Impi
{

	class Vector3
	{
	public:
		real x;
		real y;
		real z;


		// pad : suorituskykyparannus, jos kääntäjä ja arkkitehtuuri operoi nelisanaisesti.
		// Seuraavaksiko siis tietokonearkkitehtuurin kurssille?
	private:
		real pad;

	public:
		Vector3() : x(0), y(0), z(0), pad(0) {}

			Vector3(const real x,
					const real y,
					const real z) : x(x), y(y), z(z) { }

	

			// SIVUVAIKUTUKSELLISET

			// Skalaaritulo
			void operator*=(const real value)
			{
				x *= value;
				y *= value;
				z *= value;
			}

			void operator+=(const Vector3& v)
				{
					x += v.x;
					y += v.y;
					z += v.z;
				}

			void operator-=(const Vector3& v)
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
				}

			void addScaledVector(const Vector3& v, real scale)
			{
				x += v.x * scale;
				y += v.y * scale;
				z += v.z * scale;
			}

			void componentProductUpdate(const Vector3& vec)
			{
				x *= vec.x;
				y *= vec.y;
				z *= vec.z;
			}

			//UUDEN VEKTORIN PALAUTTAVAT

			Vector3 operator+(const Vector3& v) const
			{
				return Vector3(x + v.x, y + v.y, z + v.z);
			}

			Vector3 operator*(const real value) const
			{
				return Vector3(x * value, y * value, z * value);
			}

			Vector3 operator-(const Vector3& v) const
			{
				return Vector3(x - v.x, y - v.y, z - v.z);
			}


			// TULOT
		
			Vector3 componentProduct(const Vector3& vec) const
			{
				return Vector3(x * vec.x, y * vec.y, z * vec.z);
			}

			real scalarProduct(const Vector3& vector) const
			{
				return x * vector.x + y * vector.y + z * vector.z;
			}

			real operator*(const Vector3& vector) const
			{
				return x * vector.x + y * vector.y + z * vector.z;
			}

			Vector3 cross(const Vector3& vector) const
			{
				return Vector3(y * vector.z - z * vector.y,
					z * vector.x - x * vector.z,
					x * vector.y - y * vector.x);
			}

			void operator %=(const Vector3 &vector)
			{
				*this = cross(vector);
			}
			

			


			

			// NORMIT

			void invert()
			{
				x = -x;
				y = -y;
				z = -z;
			}

			real magnitude() const
			{
				return real_sqrt(x * x + y * y + z * z);
			}

			real squared_Magnitude() const
			{
				return real(x * x + y * y + z * z);
			}



			void normalize()
			{
				real l = magnitude();
				if (l > 0)
				{
					(*this) *= ((real)1) / l;
				}
			}

	};

}
		
