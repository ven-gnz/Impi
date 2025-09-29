#define GLFW_INCLUDE_NONE



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <data/Scene.h>
#include "src/rendering/core/Shader.h"
#include <iostream>


Scene scene;
SphereMesh sphereMesh;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);



int main(void)
{
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

    while (!glfwWindowShouldClose(window))
    {
     
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        scene.update(delta);


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
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        RenderableParticle p;
        p.mesh = &sphereMesh;
        p.setPosition(Vector3(0, 5, 0));
        p.setVelocity(Vector3(5, 5, 0));

        p.radius = 0.5f;
        scene.particles.push_back(p);

    }
}

