

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <data/Scene.h>
#include "src/rendering/core/Shader.h"
#include <iostream>


SphereMesh sphereMesh;
Scene* current_scene = nullptr;


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

    // jossakin vaiheessa olisi kiva olioistaa lisää tätä boileria, tai ei nyt boileria vaan per scene asiaa tuonne scenee
    Scene ballistics("ballistics");

    current_scene = &ballistics;

    std::string sp = ballistics.getName(); // shader path prefix
    std::string vs = sp + "/shader.vert";
    const char *vertex_source = vs.c_str();
    std::string fs = sp + "/shader.frag";
    const char* frag_source = fs.c_str();
    Shader ballisticShader(vertex_source, frag_source, nullptr);

    while (!glfwWindowShouldClose(window))
    {
     
        float currentTime = (float)glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        ballistics.update(delta);
       
        ballistics.draw(ballisticShader.ID);

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



