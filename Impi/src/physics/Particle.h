#pragma once

#include "math/Vector3.h"

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

	const Vector3 getVelocity() const { return velocity;  }

	void setDamping(const float damp) { damping = damp; }

	real getMass() { return inverseMass; }

	void setMass(const real mass) { inverseMass = (real)1.0/mass; }

	bool hasFiniteMass() { return inverseMass > 0.0; }

	void addForce(const Vector3& force);

	void setAcceleration(const Vector3& ac) { acceleration = ac; }

	void clearAccumulator() { accumulatedForce = Vector3(0.0, 0.0, 0.0); }




};