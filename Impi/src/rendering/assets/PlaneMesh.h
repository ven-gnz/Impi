#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct PlaneMesh {

	unsigned int vao = 0;
	unsigned int vbo = 0;

	void createPlane(float size = 10.0f, float y = -0.25f)
	{
        float planeVertices[] = {
            // positions          // normals         // texcoords
             size, y,  size,  0.0f, 1.0f, 0.0f,  size,  0.0f,
            -size, y,  size,  0.0f, 1.0f, 0.0f,  0.0f,  0.0f,
            -size, y, -size,  0.0f, 1.0f, 0.0f,  0.0f,  size,
             size, y,  size,  0.0f, 1.0f, 0.0f,  size,  0.0f,
            -size, y, -size,  0.0f, 1.0f, 0.0f,  0.0f,  size,
             size, y, -size,  0.0f, 1.0f, 0.0f,  size,  size
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

        int stride = 8 * sizeof(float);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

	}

    void draw() const {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};