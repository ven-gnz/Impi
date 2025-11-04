#include "ClothParticle.h"
#include <iostream>



	void ClothParticle::integrate(real dt)
	{

		if (!movable) return;

		Vector3 accel = accumulatedForce * inverseMass;
		
		Vector3 temp = position;
		Vector3 velocity = (position - previousPos) * (1.0f - damping);
		position = position + velocity + accel * (dt * dt);

		previousPos = temp;

		clearAccumulator();

	}


	void ClothParticle::immobilise() { movable = false; }

	
