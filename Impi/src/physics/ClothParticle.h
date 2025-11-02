#pragma once
#include "Particle.h"
#include "src/math/Vector3.h"


/**
* A particle for simulating cloths. Overrides default integration with Verlet.
*/
class ClothParticle : public Particle
{
protected:
	Vector3 previousPos;
	bool movable;


public:


	ClothParticle() = default;
	/** 
	 Verlet integratable particle requires a initial position for particle to be able to integrate. The preferred constructor expects this position Vector.
	*/
	ClothParticle(const Vector3& pos, real mass = 1.0)
		: Particle(pos, mass, Vector3(0, 0, 0), 0.99), // call base constructor
		previousPos(pos),
		movable(true)
	{
		// Nothing else needed, base constructor sets position, inverseMass, damping, etc.
	}
	
	/**
	* Verlet Integration requires information on the previous position. Updated inside method to satisfy constraint.
	*/
	void integrate(real dt) override;

	void immobilise();


};