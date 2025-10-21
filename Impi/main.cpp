

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <scenes/Scene.h>
#include "src/rendering/core/Shader.h"
#include "src/scenes/ballistics/Ballistics.h"
#include <rendering/core/Camera.h>
#include <iostream>
#include <stdlib.h>


SphereMesh sphereMesh;
Scene* current_scene = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);

static const int windowHeight = 720;
static const int windowWidth = 1080;
float near = 0.5f;
float far = 50.0f;
float aspect = windowWidth / (float)windowHeight;
float fov = glm::radians(60.0f);
float delta;

Camera camera{};


int main(void)
{

 
    char* path;
    _get_pgmptr(&path);
    std::cout << path << std::endl;
// debug : pwd

    GLFWwindow* window;


    if (!glfwInit())
        return -1;

    
    window = glfwCreateWindow(windowWidth, windowHeight, "Impi", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);
    float lastTime = (float)glfwGetTime();

    glm::mat4 projection = glm::perspective(fov, aspect, near, far);
    glm::mat4 view = camera.GetViewMatrix();

    Ballistics ballistics;
    current_scene = &ballistics;

    current_scene->initUBO();
    current_scene->groundShader.use();
    current_scene->updateUBO(view, projection, camera.getPosition());

    while (!glfwWindowShouldClose(window))
    {
     
        float currentTime = (float)glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);

        projection = glm::perspective(fov, aspect, near, far);
        view = camera.GetViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        current_scene->update(delta);
        current_scene->draw(view, projection, camera.getPosition());


        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    sphereMesh.destroySphereMesh();
    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        
        camera.ProcessKeyboard(FORWARD, delta);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, delta);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, delta);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, delta);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (current_scene)
    {
        current_scene->onMouseButton(window, button, action, mods);
    }
}



