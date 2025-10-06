

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <../scenes/Scene.h>
#include "src/rendering/core/Shader.h"
#include "scenes/ballistics/Ballistics.h"
#include <iostream>
#include <stdlib.h>


SphereMesh sphereMesh;
Scene* current_scene = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);



int main(void)
{

 
    char* path;
    _get_pgmptr(&path);
    std::cout << path << std::endl;
    
   

    GLFWwindow* window;

    
    if (!glfwInit())
        return -1;

    
    window = glfwCreateWindow(1080, 720, "Impi", NULL, NULL);
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

   
    float lastTime = (float)glfwGetTime();

    Ballistics ballistics;
    current_scene = &ballistics;

    glm::mat4 projection;
    glm::mat4 view;

    while (!glfwWindowShouldClose(window))
    {
     
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;


        current_scene->update(delta);
        current_scene->draw(projection, view);

        glClear(GL_COLOR_BUFFER_BIT);

        
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



