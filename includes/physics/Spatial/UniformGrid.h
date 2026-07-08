#pragma once

#include <unordered_map>
#include <physics/Spatial/BroadPhase.h>
#include <physics/RigidBody_System/Contact.h>
#include <physics/RigidBody_System/CollisionPrimitives.h>


namespace Impi
{

	struct GridCell
	{
		int x;
		int y;
		int z;

		bool operator==(const GridCell& o) const
		{
			return x == o.x &&
				y == o.y &&
				z == o.z;
		}
	};

	/*
	* A simplification on hugi's algorithm - using map instead of custom hash table so bucket size is handled by STL functionality
	* https://hugi.scene.org/online/hugi32/hugi%2032%20-%20coding%20corner%20jezeus%20hash%20tables%20for%20physical%20based%20simulations.htm
	*/

	struct GridCellHash
	{
		size_t operator()(const GridCell& cell) const
		{
			constexpr size_t p1 = 73856093;
			constexpr size_t p2 = 19349663;
			constexpr size_t p3 = 83492791;

			return  cell.x * p1 ^
					cell.y * p2 ^
					cell.z * p3;
		}
	};


	class UniformGrid : public BroadPhase
	{
	public:

		UniformGrid(real cellsize = 2.0f);
		void clear() override;
		void insert(CollisionPrimitive* primitive) override;
		unsigned generatePairs(PotentialContact* contacts, unsigned limit) override;

	private:
		GridCell computeCell(const Vector3& position) const;
		real cellSize;
		std::unordered_map<GridCell, std::vector<CollisionPrimitive*>, GridCellHash> cells{};
	};
}