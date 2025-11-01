#include "Constraint.h"

Constraint::Constraint(ClothParticle* p1, ClothParticle* p2)
	: p1(p1), p2(p2)
{
	Vector3 diff = p1->getPosition() - p2->getPosition();
	rest_length = diff.magnitude();
}

void Constraint::SatisfyConstraint()
{
	Vector3 from_p1_to_p2 = p2->getPosition() - p1->getPosition();
	real dist = from_p1_to_p2.magnitude();
	Vector3 correctingDifferenceVector = from_p1_to_p2 * (1 - rest_length / dist);
	
	Vector3 halfOfCorrDifV = correctingDifferenceVector * 0.5;
	p1->setPosition(p1->getPosition() + halfOfCorrDifV);
	p2->setPosition(p2->getPosition() + halfOfCorrDifV);

}