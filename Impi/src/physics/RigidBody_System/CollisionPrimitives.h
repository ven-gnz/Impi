#pragma once
#include "Contact.h"


namespace Impi
{



class CollisionPrimitive
{
public:

	RigidBody* body;
	Matrix4 offset;
	const Vector3 getAxis(unsigned index) const
	{
		return transform.getAxisVector(index);
	}
	Matrix4 getTransform() const { return transform; }

	virtual void calculateInternals()
	{
		// if (!body) { std::cout << "Colliders body is null!\n"; return; }
		transform = body->getTransformMatrix() * offset;
	}

protected:
	Matrix4 transform;
};


class CollisionSphere : public CollisionPrimitive
{
public:

	real radius;
};

class CollisionPlane
{
public:
	Vector3 direction;
	real offset;

};

class CollisionBox : public CollisionPrimitive
{
public:
	Vector3 halfSize;
	/*
	* Projects the halfsize to the desired axis
	*/
	inline real projectToAxis(const Vector3& axis) const
	{
		return
				halfSize.x * real_abs(axis.dot(getAxis(0))) +
				halfSize.y * real_abs(axis.dot(getAxis(1))) +
				halfSize.z * real_abs(axis.dot(getAxis(2)));
	}
	
};


}