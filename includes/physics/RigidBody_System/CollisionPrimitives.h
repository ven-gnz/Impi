#pragma once
#include <physics/RigidBody_System/Contact.h>


namespace Impi
{

	struct AABB
	{
		Vector3 min;
		Vector3 max;
	};


class CollisionPrimitive
{
public:

	RigidBody* body = nullptr;
	Matrix4 offset;
	const uint32_t ID;
	inline virtual AABB getAABB() const = 0;

	CollisionPrimitive()
		: ID(nextID++) { }

	const Vector3 getAxis(unsigned index) const
	{
		return transform.getAxisVector(index);
	}

	const Matrix4& getTransform() const { return transform; }

	virtual void calculateInternals()
	{
		transform = body->getTransformMatrix() * offset;
	}

private:
	// nice c++17 ism - every translation unit can see the definition, but the linker merges them into one variable
	inline static uint32_t nextID = 0;

	
protected:
	Matrix4 transform;
	AABB worldAABB;
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

	void calculateInternals() override
	{
		CollisionPrimitive::calculateInternals();

		Vector3 extent(
			projectToAxis(Vector3(1, 0, 0)),
			projectToAxis(Vector3(0, 1, 0)),
			projectToAxis(Vector3(0, 0, 1)));

		worldAABB.min = body->getPosition() - extent;
		worldAABB.max = body->getPosition() + extent;

	}
	inline AABB getAABB() const override
	{
		return worldAABB;
	}
	
};


}