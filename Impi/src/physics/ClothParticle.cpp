#include "ClothParticle.h"


	void ClothParticle::integrate(real dt)
	{

		if (!movable) return;

		Vector3 accel = accumulatedForce * inverseMass;

		Vector3 poscopy = position;

		// x_new = x_current + (x_current - x_prev) * damping + a * dt^2
		position += (position - previousPos) * damping + accel * (dt * dt);

		previousPos = poscopy;

		clearAccumulator();

	}

	void ClothParticle::immobilise() { movable = false; }

	
