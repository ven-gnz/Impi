#include "Mesh.h"

float vertices[] = {
    // 3p 3n 2uv
    // front face
    -1, -1,  1,   0, 0, 1,   0, 0,
     1, -1,  1,   0, 0, 1,   1, 0,
     1,  1,  1,   0, 0, 1,   1, 1,
    -1,  1,  1,   0, 0, 1,   0, 1,

    // back face
    -1, -1, -1,   0, 0, -1,  0, 0,
     1, -1, -1,   0, 0, -1,  1, 0,
     1,  1, -1,   0, 0, -1,  1, 1,
    -1,  1, -1,   0, 0, -1,  0, 1,
};

unsigned int indices[] = {
    // front
    0, 1, 2, 2, 3, 0,
    // right
    1, 5, 6, 6, 2, 1,
    // back
    5, 4, 7, 7, 6, 5,
    // left
    4, 0, 3, 3, 7, 4,
    // top
    3, 2, 6, 6, 7, 3,
    // bottom
    4, 5, 1, 1, 0, 4
};

void CubeMesh::createCubeMesh()
{
    indexCount = sizeof(indices) / sizeof(indices[0]);
    uploadToGPU();
}

void CubeMesh::uploadToGPU()
{

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(0 *sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

}

void CubeMesh::render() const
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_FLOAT, 0);
}