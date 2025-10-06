#include "Ballistics.h"
#include "../headers/rendering/assets/SphereMesh.h"
SphereMesh mesh;

Ballistics::Ballistics()
    :Scene("Ballistics",
        "scenes/ballistics/shaders/shader.vert",
        "scenes/ballistics/shaders/shader.frag",
        nullptr)
{
    {

    }
}


    void Ballistics::onMouseButton(GLFWwindow * window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            RenderableParticle p;
            p.mesh = &mesh;
            p.setPosition(Vector3(0, 5, 0));
            p.setVelocity(Vector3(5, 5, 0));
            p.radius = 0.5f;

            particles.push_back(p);
        }

    }