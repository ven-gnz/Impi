#include "ClothParticle.h"



	
	ClothParticle::ClothParticle(const Vector3& pos, real iMass)
	{
		position = pos;
		previousPos = pos;
		iMass = inverseMass;
		movable = true;
		velocity = Vector3(0, 0, 0);
		acceleration = Vector3(0, 0, 0);
		accumulatedForce = Vector3(0, 0, 0);
		damping = 0.95f;
	}

	void ClothParticle::integrate(real dt)
	{

		if (!movable) return;

		Vector3 accel = acceleration;

		accel.addScaledVector(accumulatedForce, inverseMass);

		Vector3 poscopy = position;

		// x_new = x_current + (x_current - x_prev) * damping + a * dt^2
		position += (position - previousPos) * damping + accel * (dt * dt);

		previousPos = poscopy;

		clearAccumulator();

	}

	void ClothParticle::immobilise() { movable = false; }

	
