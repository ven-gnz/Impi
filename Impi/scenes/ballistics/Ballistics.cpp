#include "Ballistics.h"
#include "../src/rendering/assets/SphereParticle.h"

Ballistics::Ballistics()
    :Scene("Ballistics",
        "scenes/ballistics/shaders/shader.vert",
        "scenes/ballistics/shaders/shader.frag",
        nullptr)
{
    {
        mesh.createMesh(1.0f);
        mesh.uploadToGPU();
        scenemesh = &mesh;
    }
}


    void Ballistics::onMouseButton(GLFWwindow * window, int button, int action, int mods)
    {

        Vector3 particleSpawn(Vector3(0, 1, 0));
        Vector3 particleVelocity(Vector3(0.25, 0.25, 0));
        float dumping = 0.95f; // dummy +- damping - iterating on the name still
        float ima = 1.0f;

        std::cout << "on mouse button on ballistics" << std::endl;
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

            Particle p;
            p.setPosition(particleSpawn);
            p.setVelocity(particleVelocity);
            p.setDamping(dumping);
            p.setInvMass(ima);
            particles.push_back(p);
            Particle* ptr = &particles.back();
            renderables.push_back(RenderableParticle(ptr, scenemesh, 1.5f));
        }

    }