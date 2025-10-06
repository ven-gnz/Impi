#include <rendering/assets/SphereMesh.h>
#include <vector>
#include <cmath>
#include <iostream>

void SphereMesh::createMesh(float radius, unsigned int sectorCount, unsigned int stackCount)
{
	vertices.clear();
	normals.clear();
	texCoords.clear();
	indices.clear();

	const float PI = 3.14159265358979323846f;

	float x, y, z, xy; // vpos
	float nx, ny, nz, lengthInv = 1.0f / radius; // vertex normal
	float s, t; // vertex texCoord

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (unsigned int i=0; i <= stackCount; ++i)
	{
		// pituusasteet
		stackAngle = PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle); // r * cos(u), u
		z = radius * sinf(stackAngle);

		// leveysasteet

		for (unsigned int j=0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			// https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back
			//vertices.emplace_back(x,y,z);
			vertices.push_back(glm::vec3(x,y,z));

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(glm::vec3(nx, ny, nz));
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(glm::vec2(s, t));

		}

	}


	// k1--k1+1
	// |  / |
	// | /  |
	// k2--k2+1
	for (unsigned int i=0; i < stackCount; ++i)
	{
		unsigned int k1 = i * (sectorCount + 1);
		unsigned int k2 = k1 + sectorCount + 1;

		for (unsigned int j=0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != stackCount - 1)
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	indexCount = (unsigned int)indices.size();

}


/*
 v v v n n n u v,
 3 v, 3 n, 2 t
*/
std::vector<float> SphereMesh::flatten() const
{
	std::vector<float> flatdata;
	flatdata.reserve(vertices.size() * 8);

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		const glm::vec3& v = vertices[i];
		const glm::vec3& n = normals[i];
		const glm::vec2& uv = texCoords[i];

		flatdata.push_back(v.x);
		flatdata.push_back(v.y);
		flatdata.push_back(v.z);

		flatdata.push_back(n.x);
		flatdata.push_back(n.y);
		flatdata.push_back(n.z);

		flatdata.push_back(uv.x);
		flatdata.push_back(uv.y);

	}

	return flatdata;
}

void SphereMesh::uploadToGPU()
{

	std::vector<float> flatdata = flatten();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, flatdata.size() * sizeof(float), flatdata.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	GLsizei stride_ptr = (3 + 3 + 2) * sizeof(float);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride_ptr, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride_ptr, (void*)3);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride_ptr, (void*)6);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void SphereMesh::destroySphereMesh()
{
	if (ebo) glDeleteBuffers(1, &ebo);
	if (vbo) glDeleteBuffers(1, &vbo);
	if (vao) glDeleteBuffers(1, &vao);
	vao = vbo = ebo = 0;
}

void SphereMesh::draw() const
{
	std::cout << "drawing mesh" << std::endl;
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}