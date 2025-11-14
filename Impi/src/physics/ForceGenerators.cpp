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

	Vector3 worldAnchor = body->getPointInWorldSpace(connectionPoint);
	std::cout << "Spring anchor world pos: " << worldAnchor << std::endl;

	Vector3 worldPos = body->getPosition();
	Matrix4 m = body->getTransformMatrix();
	std::cout << "Transform translation: ("
		<< m.data[3] << ", " << m.data[7] << ", " << m.data[11] << ")" << std::endl;
	// Calculate the two ends in world space.
	Vector3 lws = body->getPointInWorldSpace(connectionPoint);
	Vector3 ows = other->getPointInWorldSpace(otherConnectionPoint);
	// Calculate the vector of the spring.
	Vector3 force = lws - ows;
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

Spring::Spring()
	: connectionPoint(0, 0, 0),
	other(nullptr),
	otherConnectionPoint(0, 0, 0),
	springConstant(0),
	restLength(0)
{
}


Vector3 Spring::getAnchorWorldA(RigidBody* body) const {
	return body->getPointInWorldSpace(connectionPoint);
}

Vector3 Spring::getAnchorWorldB() const {
	return other->getPointInWorldSpace(otherConnectionPoint);
}




