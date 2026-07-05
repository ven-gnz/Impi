#include "LineMesh.h"

void LineMesh::uploadToGPU()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

}

void LineMesh::setPoints(const glm::vec3 a, const glm::vec3 b)
{
	points[0] = a;
	points[1] = b;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LineMesh::draw()
{
	glLineWidth(5.0f);
	glDrawArrays(GL_LINES, 0, 2);
}

