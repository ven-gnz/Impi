#include "Ballistics.h"
#include "../headers/rendering/assets/SphereMesh.h"
SphereMesh sphereMesh;

Ballistics::Ballistics()
    :Scene("Ballistics")
{
    {
        std::string vs = name + "/shaders/shader.vert";
        std::string fs = name + "shaders/shader.frag";
        shader = Shader(vs.c_str(), fs.c_str(), nullptr);
    }
}


    void Ballistics::onMouseButton(GLFWwindow * window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            RenderableParticle p;
            p.mesh = &sphereMesh;
            p.setPosition(Vector3(0, 5, 0));
            p.setVelocity(Vector3(5, 5, 0));
            p.radius = 0.5f;

            particles.push_back(p);
        }

    }