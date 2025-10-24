#pragma once
#include "Precision.h"
#include "Vector3.h"
namespace Impi
{

	class Random
	{
	public:

		Random();

		Random(unsigned seed);

		void seed(unsigned seed);

		unsigned rotl(unsigned n, unsigned r);

		unsigned rotr(unsigned n, unsigned r);

		unsigned randomBits();

		unsigned randomInt(unsigned max);

		real randomReal();

		real randomReal(real min, real max);

		Vector3 randomVector(const Vector3& min, const Vector3& max);

	private:
		int p1, p2;
		unsigned buffer[17];
	};
}