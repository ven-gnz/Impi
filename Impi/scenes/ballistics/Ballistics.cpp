#include "Ballistics.h"
#include "../src/rendering/assets/SphereParticle.h"
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

        std::cout << "on mouse button on ballistics" << std::endl;
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            Particle p;
            p.setPosition(Vector3(0, 1, 0));
            p.setVelocity(Vector3(0.25, 0.25, 0));
            particles.push_back(p);
            Particle* ptr = &particles.back();
            renderables.push_back(RenderableParticle(ptr, &mesh, 10.0f));
        }

    }