

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <scenes/Scene.h>
#include "rendering/core/Shader.h"
#include "scenes/ballistics/Ballistics.h"
#include "scenes/fireworks/FireWorkScene.h"
#include "scenes/ropescene/RopeScene.h"
#include <rendering/core/Camera.h>
#include <rendering/core/ViewPort.h>
#include <iostream>
#include <stdlib.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


Scene* current_scene = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);

int windowHeight = 1080;
int windowWidth = 1920;

static int scene_ptr = 0;


static ViewPort default_viewport = ViewPort{windowWidth,windowHeight};
float delta;

Camera camera {default_viewport};


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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 420");


    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);

    float lastTime = (float)glfwGetTime();

    

    Ballistics ballistics(camera);
    FireWorkScene firework(camera);
    RopeScene rop(camera);

    std::vector<Scene> scenes;
    scenes.push_back(ballistics);
    // scenes.push_back(firework);

    current_scene = &firework;

    

    while (!glfwWindowShouldClose(window))
    {

        float currentTime = (float)glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.05, 0.05, 0.05, 1.0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        current_scene->update(delta);
        current_scene->draw();

        ImGui::Begin("UI Test");
        ImGui::Text("Current Scene : %s", typeid(*current_scene).name());

        if (ImGui::Button("Switch to Ballistics")) {
            current_scene = &ballistics;
            current_scene->onActivate();
        }
        if (ImGui::Button("Switch to Fireworks")) {
            current_scene = &firework;
            current_scene->onActivate();
        }

        if (ImGui::Button("Rope")) {
            current_scene = &rop;
            current_scene->onActivate();
        }

        ImGui::Separator();
        ImGui::Text("Delta Time: %.3f ms/frame", delta * 1000.0f);
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();
       

    }

    

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

   
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
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {

    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (current_scene)
    {
        current_scene->onMouseButton(window, button, action, mods);
    }
}



