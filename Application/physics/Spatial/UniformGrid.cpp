#include <physics/Spatial/UniformGrid.h>
#include <algorithm>

using namespace Impi;

GridCell UniformGrid::computeCell(const Vector3& pos)const
{
	return
	{
		(int)std::floor(pos.x / cellSize),
		(int)std::floor(pos.y / cellSize),
		(int)std::floor(pos.z / cellSize)
	};
}

void UniformGrid::insert(CollisionPrimitive* prim)
{

	AABB bounds = prim->getAABB();

	GridCell min = computeCell(bounds.min);
	GridCell max = computeCell(bounds.max);
	// add the primitive to all the cells so the neighbor search will work
	for (int x = min.x; x <= max.x; ++x)
	{
		for (int y = min.y; y <= max.y; ++y)
		{
			for (int z = min.z; z <= max.z; ++z)
			{
				cells[{x, y, z}].push_back(prim);
			}
		}
	}



}

void UniformGrid::clear() { cells.clear(); }


unsigned UniformGrid::generatePairs(
	PotentialContact* contacts,
	unsigned limit
)
{
	std::unordered_set<uint64_t> generatedPairs;
	unsigned count = 0;

	for (auto& [cell, primitives] : cells)
	{
		for (size_t i = 0; i < primitives.size(); ++i)
		{
			for (size_t j = i + 1; j < primitives.size(); ++j)
			{
				if (!isValidPair(
					primitives[i],
					primitives[j],
					generatedPairs))
				{
					continue;
				}
				if (count >= limit) return count;
				contacts[count++] = { primitives[i], primitives[j] };
			}
		}

		//Neighbor search
		for (const GridCell& offset : forwardNeighbors)
		{
			GridCell neighbor
			{
				cell.x + offset.x,
				cell.y + offset.y,
				cell.z + offset.z,
			};

			auto it = cells.find(neighbor);

			if (it == cells.end()) continue;

			const auto& other = it->second;

			for (CollisionPrimitive* a : primitives)
			{
				for (CollisionPrimitive* b : other)
				{
					if (!isValidPair(
						a,
						b,
						generatedPairs))
					{
						continue;
					}
					if (count >= limit) return count;
					contacts[count++] = { a,b };
				}
			}
		}

	}

	std::cout << "generated pairs : " << count << std::endl;
	return count;
}

bool UniformGrid::isValidPair(
	CollisionPrimitive* a,
	CollisionPrimitive* b,
	std::unordered_set<uint64_t>& generatedPairs)
	{
	if (a == b) return true;
	if (!overlaps(a->getAABB(), b->getAABB())) return true;

	uint32_t nonConstA = a->ID;
	uint32_t nonConstB = b->ID;
	if (nonConstA > nonConstB) std::swap(nonConstA, nonConstB);

	uint64_t commonKey = (uint64_t(nonConstA)) << 32 | nonConstB;
	if (!generatedPairs.insert(commonKey).second) return false;
	return true;

}

UniformGrid::UniformGrid(real cellSize)
	: cellSize(cellSize)
{

	cells.clear();
}