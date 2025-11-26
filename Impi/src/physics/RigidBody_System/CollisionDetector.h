#pragma once
#include "CollisionPrimitives.h"

namespace Impi
{
	struct CollisionData
	{
		/**
		* Holds the first contact in the array.
		* The contact pointer is to be incremented upon detecting a contact.
		* we need a static pointer to the start of the array.
		*/
		Contact* first_contact_in_array;

		/* Holds the contact array to write into*/
		Contact* contacts;
		int contactsLeft;
		unsigned contactCount;
		real friction;
		real restitution;
		real tolerance;

		bool hasMoreContacts();
		void reset(unsigned maxContacts);
		void addContacts(unsigned count);
	};


	class CollisionDetector
	{
	public:

		static unsigned sphereAndSphere
		(const CollisionSphere& one,
			const CollisionSphere& two,
			CollisionData* data
		);

		unsigned sphereAndHalfSpace(const CollisionSphere& sphere,
			const CollisionPlane& plane,
			CollisionData* data);

		unsigned sphereAndTruePlane(const CollisionSphere& sphere,
			const CollisionPlane& plane,
			CollisionData* data);

		unsigned boxAndHalfSpace(
			const CollisionBox& box,
			const CollisionPlane& plane,
			CollisionData* data
		);

		unsigned boxAndSphere(
			const CollisionBox& box,
			const CollisionSphere& sphere,
			CollisionData* data
		);

		unsigned boxAndPoint(
			const CollisionBox& box,
			const Vector3& point,
			CollisionData* data);


		static real penetrationOnAxis(
			const CollisionBox& one,
			const CollisionBox& two,
			const Vector3& axis,
			const Vector3& tocenter
		);

		static bool tryAxis(
			const CollisionBox &one,
			const CollisionBox &two,
			Vector3 axis,
			const Vector3& tocenter,
			unsigned index,

			real& smallestPenetration,
			unsigned &smallestCase
		);

	
	

	/*
	* A vertex from box two is in contact with a face of box one.
	*/
	void generate_Point_Face_Contact(
		const CollisionBox& one,
		const CollisionBox& two,
		const Vector3& toCenter,
		CollisionData* data,
		unsigned best,
		real pen
	);

	/*
	* Finds the point on the line segments which is closer on edge - edge collision.
	*/
	Vector3 find_point_of_contact(
		const Vector3&pOne,
		const Vector3&dOne,
		real oneSize,
		const Vector3 &pTwo,
		const Vector3 &dTwo,
		real twoSize,
		// when contact happens outside of the edge ie edge - face contact:
		// use ones midpoint
		// otherwise two's midpoint can be used
		bool useOne);

	unsigned boxAndBox(
		const CollisionBox &one,
		const CollisionBox &two,
		CollisionData * data
		);

	};

}