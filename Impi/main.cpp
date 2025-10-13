

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <scenes/Scene.h>
#include "src/rendering/core/Shader.h"
#include "src/scenes/ballistics/Ballistics.h"
#include <iostream>
#include <stdlib.h>


SphereMesh sphereMesh;
Scene* current_scene = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);

static const int windowHeight = 720;
static const int windowWidth = 1080;
float near = 0.1f;
float far = 100.0f;
float aspect = windowWidth / (float)windowHeight;
float fov = glm::radians(45.0f);

glm::vec3 cameraPos(0.0f, 1.0f, 5.0f);
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);




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

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   
    float lastTime = (float)glfwGetTime();

    Ballistics ballistics;
    current_scene = &ballistics;

    glm::mat4 projection;
    glm::mat4 view;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        projection = glm::perspective(fov, aspect, near, far);
        view = glm::lookAt(cameraPos, cameraTarget, up);

        current_scene->update(delta);
        current_scene->draw(projection, view);

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
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (current_scene)
    {
        current_scene->onMouseButton(window, button, action, mods);
    }
}



