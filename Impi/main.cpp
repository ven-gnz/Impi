#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <data/Scene.h>

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

   // unsigned int VBO; // Muistetaas alustaa nämä
    // glGenBuffers(1, &VBO);

    
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

   
    float lastTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
     
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        scene.update(delta);


        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);


        
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

