#include "Fluid.h"


Fluid::Fluid(Camera &camera)
	:
    Scene("Fluid",
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

    cpuBlob blobs[2];

    blobs[0].pos = { 0.5f, 0.5f };
    blobs[0].vel = { 0.0f, 0.0f };
    blobs[0].radius = 0.05f;
    blobs[0].mass = 1.0f;
    blobs[0].pad = 0.0f;

    blobs[1].pos = { 0.0f, 0.5f };
    blobs[1].vel = { 0.0f, 0.0f };
    blobs[1].radius = 0.05f;
    blobs[1].mass = 1.0f;
    blobs[1].pad = 0.0f;

    const char* sourceCode = computeShaderCode.c_str();
    
    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, &sourceCode, NULL);
    glCompileShader(cs);

    computeProgram = glCreateProgram();
    glAttachShader(computeProgram, cs);
    glLinkProgram(computeProgram);

    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(blobs), blobs, GL_DYNAMIC_COPY);
    //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);


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

    // does not work with delta time?
    glUniform1f(glGetUniformLocation(computeProgram, "dt"), delta);
    glUniform1f(glGetUniformLocation(computeProgram, "gravity"), -0.2f);
   
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glDispatchCompute(16, 1, 1); // one invocation per blob might do?
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

// I guess we don't need the renderer or camera strictly here.
void Fluid::draw(Renderer& renderer, Camera& camera)
{
    shader.use();

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
    glUniform2f(glGetUniformLocation(shader.ID, "resolution"), width, height);
    glUniform1i(glGetUniformLocation(shader.ID, "numBlobs"), 2);

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