#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct PlaneMesh {

	unsigned int vao = 0;
    unsigned int vbo = 0;

	void createPlane(float size = 10.0f, float y = -0.25f)
	{

        float quadVertices[] = {
            
            -1.0f, -1.0f,
             1.0f, -1.0f,
            -1.0f,  1.0f,

            -1.0f,  1.0f,
             1.0f, -1.0f,
             1.0f,  1.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

	}

    void draw() const {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
};