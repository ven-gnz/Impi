#include <src/scenes/ropescene/RopeScene.h>
#include <glm/glm.hpp>

RopeScene::RopeScene(Camera& camera)
    : Scene("RopeScene",
        camera,
        "src/scenes/ropescene/shaders/rope.vert",
        "src/scenes/ropescene/shaders/rope.frag",
        nullptr
    ),
    defaultSpringConstant(8.0), defaultRestLength(1.5),
    from_cube_to_sphere(&cubePos, defaultSpringConstant, defaultRestLength),
    scene_gravity(Vector3(0.0, -9.8, 0.0)),
    sphere(Vector3(2,3,0),1.5,Vector3(3,1,0),0.01),
    cube(Vector3(0,0,0), 125.0, Vector3(0,0,0), 0.05)
{
    
    sphere_mesh.createMesh(1.0f);
    sphere_mesh.uploadToGPU();
    spheremesh_ptr = &sphere_mesh;

    particles.reserve(255);
    renderables.reserve(255);

}


void RopeScene::onActivate()
{
    Scene::onActivate();
    sphere.setPosition(Vector3(0, -3.375, 0));
    sphere.setVelocity(Vector3(0, 0, 0));
    camera.Position = camera.defaultPos + glm::vec3(0,0,15);

}


void RopeScene::update(real dt)
{
    sphere.clearAccumulator();

    scene_gravity.updateForce(&sphere, dt);
    from_cube_to_sphere.updateForce(&sphere, dt);

    //std::cout << "sphere velocity ";
    //std::cout << sphere.getVelocity().x << sphere.getVelocity().y << sphere.getVelocity().z << std::endl;
    sphere.integrate(dt);
    //std::cout << sphere.getPosition().y << " sphere pos" << std::endl;
   
}


void RopeScene::draw(Renderer& renderer, Camera& camera)
{

    renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());

    groundShader.use();
    glBindVertexArray(groundmesh_ptr->vao);
    groundmesh_ptr->draw();

    shader.use();
    
    glm::mat4 model = glm::translate(glm::mat4(1.0f),
        glm::vec3(sphere.getPosition().x, sphere.getPosition().y, sphere.getPosition().z));

    shader.setMat4("model", model);

    glBindVertexArray(sphere_mesh.vao);
    sphere_mesh.draw();

    glBindVertexArray(0);
}


// https://stackoverflow.com/questions/45130391/opengl-get-cursor-coordinate-on-mouse-click-in-c
void RopeScene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;

        Vector3 diff(
           xpos - sphere.getPosition().x,
           ypos - sphere.getPosition().y,
            0);

        std::cout << " dx : " << diff.x << " dy : " << diff.y << std::endl;
        real scaler = 0.01;

        sphere.addImpulse(diff*scaler);
    }

}