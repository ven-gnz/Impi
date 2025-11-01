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
	/**
	* Satisfies the rest length constraint between two particles by calculating the difference vector,
	and offsetting both particles by half of that amount in the direction. 
	Also known as Constraint relaxation, Positional Correction.
	*/
	void SatisfyConstraint();

};