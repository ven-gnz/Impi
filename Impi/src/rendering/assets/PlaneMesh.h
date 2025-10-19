#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct PlaneMesh {

	unsigned int vao = 0;

	void createPlane(float size = 10.0f, float y = -0.25f)
	{
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindVertexArray(0);

	}

    void draw() const {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};