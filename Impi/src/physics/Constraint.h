#pragma once
#include "ClothParticle.h"

/**
* Representation of a physical constraint between two connected particles.
*/
class Constraint
{

private:
	real rest_length;


public:
	ClothParticle* p1, * p2;

	Constraint(ClothParticle* p1, ClothParticle* p2);
	void SatisfyConstraint();

};