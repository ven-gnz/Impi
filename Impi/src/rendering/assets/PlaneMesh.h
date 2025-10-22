#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct PlaneMesh {

	unsigned int vao = 0;

	void createPlane()
	{
        glGenVertexArrays(1, &vao);
	}

    void draw() const {
        // forming the quad in vertex shader
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
    }
};