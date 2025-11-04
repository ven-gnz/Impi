#include "ClothParticle.h"
#include <iostream>


/*
	Vec3 temp = pos;
			pos = pos + (pos-old_pos)*(1.0-DAMPING) + acceleration*TIME_STEPSIZE2;
			old_pos = temp;
			acceleration = Vec3(0,0,0)
*/

	void ClothParticle::integrate(real dt)
	{

		if (!movable) return;

		Vector3 accel = accumulatedForce * inverseMass;
		
		Vector3 temp = position;
		Vector3 velocity = (position - previousPos) * (1.0f - damping);
		position = position + velocity + accel * (dt * dt);

		// pos = pos + (pos-old_pos)*(1.0-DAMPING) + acceleration*TIME_STEPSIZE2;

		previousPos = temp;

		clearAccumulator();

	}


	void ClothParticle::immobilise() { movable = false; }

	
