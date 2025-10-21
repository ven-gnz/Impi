#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct PlaneMesh {

	unsigned int vao = 0;
    unsigned int vbo = 0;

	void createPlane(float size = 10.0f, float y = -0.25f)
	{
        glGenVertexArrays(1, &vao);

	}

    void draw() const {
        glBindVertexArray(vao);
        // forming the quad in vertex shader
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
};