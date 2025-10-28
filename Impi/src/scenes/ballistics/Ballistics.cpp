#include "Ballistics.h"
#include <rendering/assets/SphereMesh.h>

Ballistics::Ballistics(Camera& camera)
    :Scene("Ballistics",
        camera,
        "src/scenes/ballistics/shaders/shader.vert",
        "src/scenes/ballistics/shaders/shader.frag",
        nullptr)
{
    {
        sphere_mesh.createMesh(1.0f);
        sphere_mesh.uploadToGPU();
        spheremesh_ptr = &sphere_mesh;
        
    }
}

void Ballistics::onActivate()
{
    camera.Position = camera.defaultPos;
}


    void Ballistics::onMouseButton(GLFWwindow * window, int button, int action, int mods)
    {

        Vector3 particleSpawn(Vector3(0, 0, 0));
        Vector3 particleVelocity(Vector3(0.0, 1.0, -1.0));
        float dumping = 0.95f; // dummy +- damping - iterating on the name still
        float mass = 16.0f;

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

            Particle p;
            p.setPosition(particleSpawn);
            p.setVelocity(particleVelocity);
            p.setDamping(dumping);
            p.setMass(mass);
            particles.push_back(p);
            Particle* ptr = &particles.back();
            renderables.push_back(RenderableParticle(ptr, spheremesh_ptr, 0.5f));
        }

    }