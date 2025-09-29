#pragma once

#include "Vector3.h"

using namespace Impi;

class Particle
{
protected:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	Vector3 accumulatedForce;
	real damping;
	real inverseMass;

public:

	void integrate(real duration);

	const Vector3& getPosition() const { return position; }
	void setPosition(const Vector3& np) { position = np; }

	void setVelocity(const Vector3& v) { velocity = v; }
};