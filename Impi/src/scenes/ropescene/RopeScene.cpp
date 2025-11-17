#include <src/scenes/ropescene/RopeScene.h>
#include <glm/glm.hpp>

RopeScene::RopeScene(Camera& camera)
    : Scene("RopeScene",
        camera,
        "src/scenes/ropescene/shaders/rope.vert",
        "src/scenes/ropescene/shaders/rope.frag",
        nullptr
    ),
    cubePos(0,3.375,0),
    defaultSpringConstant(8.0), defaultRestLength(1.5),
    from_cube_to_sphere(&cubePos, defaultSpringConstant, defaultRestLength),
    scene_gravity(Vector3(0.0, -9.8, 0.0)),
    sphere(Vector3(0,0,0),1.5,Vector3(0,0,0),0.01),
    cube(Vector3(0,3.375,0), 125.0, Vector3(0,0,0), 0.05),
    canKick(true),
    kickCD(3.0f),
    kickTimer(3.0f)
{
    shader.use();
    sphere_mesh.createMesh(1.0f);
    sphere_mesh.uploadToGPU();
    spheremesh_ptr = &sphere_mesh;

    particles.reserve(255);
    renderables.reserve(255);
    lineShader.use();
    kick_magnitude.uploadToGPU();
    spring_line.uploadToGPU();
    
}


void RopeScene::onActivate()
{
    Scene::onActivate();
    sphere.setPosition(Vector3(0, 0, 0));
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

    if (!canKick)
    {
        kickTimer += dt;
        if (kickTimer >= kickCD) canKick = true;
    }
   
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
    sphere_mesh.render();
    lineShader.use();
    glBindVertexArray(spring_line.vao);
    glm::vec3 sp = glm::vec3(sphere.getPosition().x, sphere.getPosition().y, sphere.getPosition().z);
    glm::vec3 cp = glm::vec3(cubePos.x, cubePos.y, cubePos.z);
    spring_line.setPoints(sp, cp);
    lineShader.setVec3("color", glm::vec3(0.6f, 0.6f, 0.6f));
    spring_line.draw();


    if (!canKick) return;

   
    glBindVertexArray(kick_magnitude.vao);
    glm::vec3 mp = glm::vec3(lastMousePos.x, lastMousePos.y, lastMousePos.z);
    kick_magnitude.setPoints(sp, mp);
    lineShader.setVec3("color", glm::vec3(1.0f, 0.1, 0.1f));
    kick_magnitude.draw();

    glBindVertexArray(0);
}

// https://stackoverflow.com/questions/45130391/opengl-get-cursor-coordinate-on-mouse-click-in-c
Vector3 RopeScene::screenToWorld(double xpos, double ypos, GLFWwindow* window,
    glm::mat4 view, glm::mat4 proj)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float winZ = 0.5f;
    glm::vec3 worldPos = glm::unProject(
        glm::vec3((float)xpos, (float)(height - ypos), winZ),
        view,
        proj,
        glm::vec4(0, 0, width, height)
    );

    return Vector3(worldPos.x, worldPos.y, worldPos.z);
}

void RopeScene::updateMouse(GLFWwindow* window, const Renderer& renderer)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastMousePos = screenToWorld(xpos, ypos, window,
        renderer.getView(),
        renderer.getProjection());
}



void RopeScene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (!canKick) return;
        Vector3 diff =  sphere.getPosition() - lastMousePos;
        diff.z = sphere.getPosition().z;
       
        real scaler =  diff.magnitude() * 50;

        sphere.addImpulse(diff.normalized()*scaler);
        
        canKick = false;
        kickTimer = 0.0f;
    }

}