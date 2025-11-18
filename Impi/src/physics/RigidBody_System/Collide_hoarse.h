#pragma once

#include <src/physics/RigidBody_System/RigidBody.h>

namespace Impi
{



	struct PotentialContact
	{
		RigidBody* body[2];
	};

	template<class BoundingVolumeClass>
	class BVHNode
	{
	public:
		BVHNode* children[2];
		BVHNode* parent;
		BoundingVolumeClass volume;

		RigidBody* body;

		bool isLeaf() const { return (body != NULL); }

		unsigned getPotentialContacts(PotentialContact* contacts, unsigned limit) const;

		

		void insert();

	protected:

		bool overlaps(const BVHNode<BoundingVolumeClass>* other) const;
		
		unsigned getPotentialContactsWith(
			const BVHNode<BoundingVolumeClass>* other,
			PotentialContact* contacts,
			unsigned limit) const;

		void recalculateBoundingVolume(bool recurse = true);
			
	};



}