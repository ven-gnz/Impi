#include "BoxBoxScene.h"




void Box::updateModelMatrix(){

        float mat[16];
        body.getGLTransform(mat);
        model = glm::scale(glm::make_mat4(mat), scaler);

}


BoxBoxScene::BoxBoxScene(Camera& camera)
    : Scene("Box",
        camera,
        "src/scenes/BoxBox/shaders/box.vert",
        "src/scenes/BoxBox/shaders/box.frag",
        nullptr),
    cData(),
    scene_gravity(),
    ammoRigidBodies(), boxes(), renderables(),
    detector(),
        cubePositions{ 
            Vector3(0,4,0),
            Vector3(6, 7, 0),
            Vector3(5, 10, 0),
            Vector3(4, 5, 1) },
        groundPlane()
{
    ammoRigidBodies.reserve(128);
    boxes.reserve(16);

   
    groundPlane.direction = Vector3(0, 1, 0);
    groundPlane.offset = real(0.01);

    cubeMesh.createCubeMesh();
    cubeMesh.uploadToGPU();
    cubemesh_ptr = &cubeMesh;



    for (auto& position : cubePositions)
    {
        Box b;

        b.body = RigidBody(position);
        b.collider.halfSize = Vector3(0.5, 0.5, 0.5);
        b.mesh_ptr = cubemesh_ptr;
        b.model = glm::mat4(1.0f);
        b.scaler = glm::vec3(1.0f);
        boxes.push_back(b);

    }

    for (Box& b : boxes)
    {
        registry.add(&b.body, &scene_gravity);
    }


}




void BoxBoxScene::draw(Renderer& renderer, Camera& camera)
{

    renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());

    groundShader.use();
    glBindVertexArray(groundmesh_ptr->vao);
    groundmesh_ptr->draw();

    shader.use();

    glBindVertexArray(cubemesh_ptr->vao);
    shader.setVec3("color", glm::vec3(1.0, 0.4, 0.3));

    for (auto& box : boxes)
    {
        
        box.updateModelMatrix();
        shader.setMat4("model", box.model);
        box.mesh_ptr->render();
        
    }



}
void BoxBoxScene::update(real dt)
{

    generateContacts();

   
    registry.updateForces(dt);

    for (auto& box : boxes)
    {
       box.body.integrate(dt);

       
    }





    


  

   

}


void BoxBoxScene::onActivate()
{
    camera.Position = camera.Position + glm::vec3(0, 0, 5);
}


void BoxBoxScene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

void BoxBoxScene::updateMouse(GLFWwindow* window, const Renderer& renderer)
{

}

void BoxBoxScene::generateContacts()
{

    cData.reset(maxContacts);
    cData.friction = (real)0.9;
    cData.restitution = (real)0.1;
    cData.tolerance = (real)0.1;

    for (auto& box : boxes)
    {
        if (!cData.hasMoreContacts()) return;

        detector.boxAndHalfSpace(box.collider, groundPlane, &cData);

    }

}