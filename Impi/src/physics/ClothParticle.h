#pragma once
#include "Particle.h"


/**
* A particle for simulating cloths. Overrides default integration with Verlet.
*/
class ClothParticle : public Particle
{
protected:
	Vector3 previousPos;


public:

	ClothParticle() = default;
	/** 
	 Verlet integratable particle requires a initial position for particle to be able to integrate. The preferred constructor expects this position Vector.
	*/
	ClothParticle(const Vector3& pos, real iMass = 1.0);
	
	/**
	* Verlet Integration requires information on the previous position. Updated inside method to satisfy constraint.
	*/
	void integrate(real dt) override;


};