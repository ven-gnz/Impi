#include <scenes/FireWorkScene.h>
#include <physics/Objects/Firework.h>

using namespace Impi;

FireWorkScene::FireWorkScene(Camera& camera)
    : Scene("Fireworks",
        camera,
        "shaders/fireworks.vert",
        "shaders/fireworks.frag",
        nullptr)
{
    camera.Position = camera.defaultPos + glm::vec3(0.0f, 0.0f, 30.0f);
    init_datastream();
    
}

void FireWorkScene::onActivate()
{
    Scene::onActivate();    
    camera.Position = camera.defaultPos + glm::vec3(0.0f, 0.0f, 30.0f);
    
}

void FireWorkScene::update(real dt)
{
    physicsWorld.update(dt);
}



void FireWorkScene::draw(Renderer& renderer, Camera& camera)
{
    renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());
    shader.use();


    //view_UBO_Debug_Data();

    shader.use();
    renderableFireworks.reserve(maxFireworks * sizeof(renderableFireworks));
    
    fill_renderbuffer();
    upstream_renderbuffer();

    glBindVertexArray(fireworkscene_VAO);
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(renderableFireworks.size()));
    glBindVertexArray(0);

}

void FireWorkScene::init_datastream()
{

    glGenVertexArrays(1, &fireworkscene_VAO);
    glGenBuffers(1, &fireworkscene_VBO);

    glBindVertexArray(fireworkscene_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, fireworkscene_VBO);

    glBufferData(GL_ARRAY_BUFFER, maxFireworks * sizeof(RenderableFirework), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RenderableFirework), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(RenderableFirework), (void*)offsetof(RenderableFirework, color));


}

glm::vec4 FireWorkScene::getCol(unsigned type)
{
    switch (type)
    {
    case 1: return { 1.0f, 0.0f, 0.0f, 1.0 };
    case 2: return { 1.0f, 0.5f, 0.0f, 1.0 };
    case 3: return { 1.0f, 1.0f, 0.0f, 1.0 };
    case 4: return { 0.0f, 1.0f, 0.0f, 1.0 };
    case 5: return { 0.0f, 1.0f, 1.0f, 1.0 };
    case 6: return { 0.4f, 0.4f, 1.0f, 1.0 };
    case 7: return { 1.0f, 0.0f, 1.0f, 1.0 };
    case 8: return { 1.0f, 1.0f, 1.0f, 1.0 };
    case 9: return { 1.0f, 0.5f, 0.5f, 1.0 };
    default: return { 1.0f, 0.5f, 0.5f, 1.0 };
    }
}

void FireWorkScene::fill_renderbuffer()
{

    auto toGLM = [](const Vector3& v) { return glm::vec4(v.x, v.y, v.z, 1.0); };
    renderableFireworks.clear();
    //std::cout << "size of fireworks " << physicsWorld.getFireworkSystem().getFireworks().size();
    for (Firework& f : physicsWorld.getFireworkSystem().getFireworks())
    {
        if (f.type > 0)
        {
            RenderableFirework r = { toGLM(f.getPosition()), getCol(f.type) };
            /*std::cout << "Rendering firework at: " << r.pos.x << ", "
                << r.pos.y << ", " << r.pos.z << std::endl;*/
            renderableFireworks.push_back(r);

        }
    }
}

void FireWorkScene::upstream_renderbuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, fireworkscene_VBO);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        renderableFireworks.size() * sizeof(RenderableFirework),
        renderableFireworks.data()
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FireWorkScene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        unsigned fireworkType = 1;
        physicsWorld.getFireworkSystem().create(fireworkType, 1, nullptr);
        //create(fireworkType, 1, nullptr);
    }
}




