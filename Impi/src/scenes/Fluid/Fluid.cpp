#include "Fluid.h"


Fluid::Fluid(Camera &camera)
	:
    Scene("RopeScene",
        camera,
        "src/scenes/Fluid/shaders/fluid.vert",
        "src/scenes/Fluid/shaders/fluid.frag",
        nullptr)
{

    const char* shaderPath = "src/scenes/Fluid/shaders/fluid.comp";

    std::cout << "compute path" << shaderPath << std::endl;
    std::string computeShaderCode;
    std::ifstream filestream;

    filestream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        filestream.open(shaderPath);

        std::stringstream computeShaderStream;

        computeShaderStream << filestream.rdbuf();

        filestream.close();

        computeShaderCode = computeShaderStream.str();


    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Compute shader file not read on Fluid scene constructor" << std::endl;
    }

    const char* sourceCode = computeShaderCode.c_str();
    
    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, &sourceCode, NULL);
    glCompileShader(cs);

    computeProgram = glCreateProgram();
    glAttachShader(computeProgram, cs);
    glLinkProgram(computeProgram);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, width, height);
    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    float quadVertices[] = {
        -1.f, -1.f, 0.f, 0.f, // 2pos 2tex
         1.f, -1.f, 1.f, 0.f,
        -1.f,  1.f, 0.f, 1.f,
        -1.f,  1.f, 0.f, 1.f,
         1.f, -1.f, 1.f, 0.f,
         1.f,  1.f, 1.f, 1.f
    };

    GLuint vbo;
    glGenVertexArrays(1, &texVAO);
    glGenBuffers(1, &vbo);

    glBindVertexArray(texVAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}

void Fluid::update(real delta)
{
    glUseProgram(computeProgram);
    glDispatchCompute(width / 16, height / 16, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

// I guess we don't need the renderer or camera strictly here.
void Fluid::draw(Renderer& renderer, Camera& camera)
{
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader.ID, "fluidTexture"), 0);

    glBindVertexArray(texVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Fluid::onActivate()
{

}

void Fluid::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

void Fluid::updateMouse(GLFWwindow* window, const Renderer& renderer)
{

}