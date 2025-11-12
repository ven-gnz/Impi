#include "ForceGenerators.h"
#include <iostream>
using namespace Impi;

Gravity::Gravity()
{
	gravity = Vector3(0, -9.8, 0);
}

Gravity::Gravity(const Vector3& gravity)
	: gravity(gravity) { }


void Gravity::updateForce(RigidBody* body, real duration)
{
	if (!body->hasFiniteMass()) return;
	body->addForce(gravity * body->getMass());
}



Spring::Spring(const Vector3& localConnectionPt,
	RigidBody* other,
	const Vector3& otherConnectionPoint,
	real springConstant,
	real restLength) 
	:
	connectionPoint(localConnectionPt),
	other(other),
	otherConnectionPoint(otherConnectionPoint),
	springConstant(springConstant),
	restLength(restLength) { }

void Spring::updateForce(RigidBody* body, real duration)
{
	// Calculate the two ends in world space.
	Vector3 lws = body->getPointInWorldSpace(connectionPoint);
	Vector3 ows = other->getPointInWorldSpace(otherConnectionPoint);
	// Calculate the vector of the spring.
	Vector3 force = lws - ows;
	std::cout << "force : " << force.x << " " << force.y << " " << force.z  << std::endl;
	// Calculate the magnitude of the force.
	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;
	// Calculate the final force and apply it.
	force.normalize();
	force *= -magnitude;
	body->addForceAtPoint(force, lws);
}

TorqueGenerator::TorqueGenerator() {}

void TorqueGenerator::setTorque(const Vector3& t)
{
	torque = t;
}

void TorqueGenerator::updateForce(RigidBody* body, real duration)
{
	body->addTorque(torque);
}

