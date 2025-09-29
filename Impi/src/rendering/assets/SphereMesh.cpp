#include <rendering/assets/SphereMesh.h>
#include <vector>
#include <cmath>

void SphereMesh::createMesh(float radius, unsigned int sectorCount, unsigned int stackCount)
{
	vertices.clear();
	normals.clear();
	texCoords.clear();
	indices.clear();

	const float PI = 3.14159265358979323846f;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	float x, y, z, xy; // vpos
	float nx, ny, nz, lengthInv = 1.0f / radius; // vertex normal
	float s, t; // vertex texCoord

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i{ 0 }; i <= stackCount; ++i)
	{
		// pituusasteet
		stackAngle = PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle); // r * cos(u), u
		z = radius * sinf(stackAngle);

		// leveysasteet

		for (int j{ 0 }; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(glm::vec3(nx,ny,nz));

		}

	}

}