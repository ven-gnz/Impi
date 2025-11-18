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

	template<class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::overlaps(
		const BVHNode<BoundingVolumeClass>* other
	) const
	{
		return volume->overlaps(other->volume);
	}

	template<class BoundingVolumeClass>
	unsigned BVHNode<BoundingVolumeClass>::getPotentialContacts(
		PotentialContact* contacts, unsigned limit
	) const
	{
		// Early out if we don't have the room for contacts, or
		// if we're a leaf node.
		if (isLeaf() || limit == 0) return 0;

		// Get the potential contacts of one of our children with
		// the other
		return children[0]->getPotentialContactsWith(
			children[1], contacts, limit
		);
	}

	template<class BoundingVolumeClass>
	unsigned BVHNode<BoundingVolumeClass>::getPotentialContactsWith(
		const BVHNode<BoundingVolumeClass>* other,
		PotentialContact* contacts,
		unsigned limit
	) const
	{
		if!overlaps(other) || limit == 0)return 0;

		if (isLeaf() && other->isLeaf())
		{
			contacts->body[0] = body;
			contacts->body[1] = other->body;
			return 1;
		}

		// Determine which node to descent into. Descending to the larger volume if neither are leaves.
		if (other->isLeaf() ||
			(!isLeaft() && volume()->getSize() >= other - volume->getSize()))
		{
			unsigned count = children[0]->getPotentialContactsWith(
				other, contacts, limit
			);
			// Check whether enough slots remain to recurse other side as well
			if (limit > count)
			{
				return count + children[1]->getPotentialContactsWith(
					other, contacts + count, limit - count);
			}
			else
			{
				return count;
			}
		}
		else
		{
			unsigned count = getPotentialContactsWith(
				other->children[0], contacts, limit);

			if (limit > count)
			{
				return count + getPotentialContactsWith(
					other->children[1], contacts + count, limit - count);
			}
			else
			{
				return count;
			}
		}


	}


}