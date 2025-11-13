#pragma once
#include <glm/glm.hpp>
#include "src/rendering/core/Shader.h"

class LineMesh
{

public:

    glm::vec3 points[2];
    glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

    unsigned int vao = 0;
    unsigned int vbo = 0;

    void uploadToGPU();

    void setPoints(const glm::vec3 a, const glm::vec3 b);

    void draw();

};