#pragma once

#include "math/Vector3.h"

using namespace Impi;

/**
 * @class Particle
 * @brief Represents a simple particle with position, velocity, mass and damping
 *
 */
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

	/**
	* @brief Constructs a new Particle.
	*
	* @param position	initial position(World Space)
	* @param mass		mass of the object(handled inversely)
	* @param velocity	initial velocity
	* @param dam		initial damping
	*/
	Particle(const Vector3& pos, real mass, const Vector3& vel, real dam);

	Particle();

	/**
	* Integrates a particle with Implicit Euler integration.
	*/
	virtual void integrate(real duration);

	const Vector3& getPosition() const { return position; }
	void setPosition(const Vector3& np) { position = np; }

	void setVelocity(const Vector3& v) { velocity = v; }

	const Vector3 getVelocity() const { return velocity; }

	void setDamping(const float damp) { damping = damp; }

	real getMass() { return inverseMass; }

	void setMass(const real mass) { inverseMass = (real)1.0/mass; }

	bool hasFiniteMass() { return inverseMass > 0.0; }

	void addForce(const Vector3& force);

	Vector3 getAcceleration();

	void setAcceleration(const Vector3& ac) { acceleration = ac; }

	void clearAccumulator() { accumulatedForce = Vector3(0.0, 0.0, 0.0); }




};