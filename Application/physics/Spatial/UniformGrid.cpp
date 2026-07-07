#include <physics/Spatial/UniformGrid.h>
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
	GridCell c = computeCell(prim->body->getPosition());
	cells[c].push_back(prim);
}

void UniformGrid::clear() { cells.clear(); }


unsigned UniformGrid::generatePairs(
	PotentialContact* contacts,
	unsigned limit
)
{
	unsigned count = 0;

	for (auto& [cell, primitives] : cells)
	{
		for (size_t i = 0; i < primitives.size(); ++i)
		{
			for (size_t j = i + 1; j < primitives.size(); ++j)
			{
				if (count >= limit) return count;

				contacts[count].first = primitives[i];
				contacts[count].second = primitives[j];

				++count;
			}
		}
	}
	return count;
}

UniformGrid::UniformGrid(real cellSize)
{
	cellSize = cellSize;
	cells.clear();
}