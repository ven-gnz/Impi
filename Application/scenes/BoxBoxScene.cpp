#include <scenes/BoxBoxScene.h>




void Box::updateModelMatrix(){

        float mat[16];
        body.getGLTransform(mat);
        model = glm::scale(glm::make_mat4(mat), scaler);

}


BoxBoxScene::BoxBoxScene(Camera& camera)
    : Scene("Box",
        camera,
        "shaders/impi_passthrough.vert",
        "shaders/impi_passthrough.frag",
        nullptr),
    cubePositions{},
        random{}
{   

    cubeMesh.createCubeMesh();
    cubeMesh.uploadToGPU();
    cubemesh_ptr = &cubeMesh;
    boxes.reserve(NUM_BOXES);


    for (int i = 0; i < NUM_BOXES; ++i)
    {
        boxes.emplace_back();
        Box& b = boxes[i];
        b.position = random.randomVector3(
            Vector3(-6, 5, -6),
            Vector3(6, 25, 6));

        b.body = RigidBody(b.position);
        b.collider.halfSize = Vector3(0.5, 0.5, 0.5);
        b.collider.offset = Matrix4();
        b.collider.body = &b.body;
        b.collider.calculateInternals();
        b.mesh_ptr = cubemesh_ptr;
        b.model = glm::mat4(1.0f);
        b.scaler = glm::vec3(1.0f);
        b.color = random.randomVector3(Vector3(0, 0, 0), Vector3(1, 1, 1));
        cubePositions.push_back(b.position);

    }

    for (Box& b : boxes)
    {
        physicsWorld.addBody(&b.body);
        physicsWorld.addCollider(&b.collider);
        physicsWorld.registerForceGenerator(&b.body, &scene_gravity);
    }


}




void BoxBoxScene::draw(Renderer& renderer, Camera& camera)
{

    renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());
    renderGroundGrid();
    shader.use();
    glBindVertexArray(cubemesh_ptr->vao);
    

    for (auto& box : boxes)
    {
        
        box.updateModelMatrix();
        shader.setMat4("model", box.model);
        shader.setVec3("color", box.color);
        box.mesh_ptr->render();
        
    }
}
void BoxBoxScene::update(real dt)
{
    physicsWorld.update(dt);
}


void BoxBoxScene::onActivate()
{
    camera.Position = camera.defaultPos + glm::vec3(0, 0, 9);

    for(size_t i = 0; i < boxes.size(); i++)
    {
        boxes[i].body.setPosition(cubePositions[i]);
    }
}


void BoxBoxScene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

void BoxBoxScene::updateMouse(GLFWwindow* window, const Renderer& renderer)
{

}

