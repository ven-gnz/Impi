#include "Constraint.h"

Constraint::Constraint(ClothParticle* p1, ClothParticle* p2)
	: p1(p1), p2(p2)
{
	Vector3 diff = p1->getPosition() - p2->getPosition();
	rest_length = diff.magnitude();
}

void Constraint::SatisfyConstraint()
{

}