#include "random.h"
#include "Vector3.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace Impi;

Random::Random()
{
	seed(0);
}

Random::Random(unsigned seed)
{
	Random::seed(seed);
}

void Random::seed(unsigned s)
{
	if (s == 0) {
		s = (unsigned)clock();
	}

	/*
	I think setting a seed for a random number deserves more time than what I have for now, will swap this out for own LCG in the future.
	*/
	// Fill the buffer with some basic random numbers
	for (unsigned i = 0; i < 17; i++)
	{
		// Simple linear congruential generator
		s = s * 2891336453 + 1;
		buffer[i] = s;
	}

	p1 = 0; p2 = 10;

}

unsigned Random::rotl(unsigned n, unsigned r)
{
	return	(n << r) |
		(n >> (32 - r));
}

unsigned Random::rotr(unsigned n, unsigned r)
{
	return	(n >> r) |
		(n << (32 - r));
}

unsigned Random::randomBits()
{
	unsigned result;

	result = buffer[p1] = rotl(buffer[p2], 13) + rotl(buffer[p1], 9);

	// Rotate pointers
	if (--p1 < 0) p1 = 16;
	if (--p2 < 0) p2 = 16;

	// Return result
	return result;
}

real Random::randomReal()
{
	// Get the random number
	unsigned bits = randomBits();

	// Set up a reinterpret structure for manipulation
	union {
		real value;
		unsigned word;
	} convert;

	// Now assign the bits to the word. This works by fixing the ieee
	// sign and exponent bits (so that the size of the result is 1-2)
	// and using the bits to create the fraction part of the float.
	convert.word = (bits >> 9) | 0x3f800000;

	// And return the value
	return convert.value - 1.0f;
}

real Random::randomReal(real min, real max)
{
	return randomReal() * (max - min) + min;
}

unsigned Random::randomInt(unsigned max)
{
	return randomBits() % max;
}

Vector3 Random::randomVector(const Vector3& min, const Vector3& max)
{
	return Vector3(
		randomReal(min.x, max.x),
		randomReal(min.y, max.y),
		randomReal(min.z, max.z)
	);
}
