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
    ammoRigidBodies(), boxes(),
    detector(),
        cubePositions{ 
            Vector3(0,3,0.1),
            Vector3(10, 4, 0.1),
            Vector3(5, 5, 0.1),
            Vector3(-5, 6, 1) },
        groundPlane(),
        resolver(maxContacts)
{
    ammoRigidBodies.reserve(128);
    boxes.reserve(16);
   
    cData.first_contact_in_array = contacts;
    cData.reset(maxContacts);

    groundPlane.direction = Vector3(0.001, 0.99, 0.001);
    groundPlane.offset = real(0);
    

    cubeMesh.createCubeMesh();
    cubeMesh.uploadToGPU();
    cubemesh_ptr = &cubeMesh;



    for (auto& position : cubePositions)
    {
        boxes.emplace_back();
        Box& b = boxes.back();
        b.body = RigidBody(position);
        b.collider.halfSize = Vector3(0.5, 0.5, 0.5);
        b.collider.offset = Matrix4();
        b.collider.body = &b.body;
        b.collider.calculateInternals();
        b.mesh_ptr = cubemesh_ptr;
        b.model = glm::mat4(1.0f);
        b.scaler = glm::vec3(1.0f);
        

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

    registry.updateForces(dt);
   
    
   
  

    for (auto& box : boxes)
    {
        box.body.integrate(dt);
        box.collider.calculateInternals();

    }

    generateContacts();
    resolver.resolveContacts(contacts, cData.contactCount, dt);

    for (auto& box : boxes)
    {
        box.body.integrate(dt);
        box.collider.calculateInternals();

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
    cData.friction = (real)0.0;
    cData.restitution = (real)0.1;
    cData.tolerance = (real)0.001;

    //std::cout << "Boxes in vector: " << boxes.size() << std::endl;

    //std::cout << cData.contactsLeft << "contacts left : " << std::endl;
    for (size_t i = 0; i < boxes.size(); ++i)
    {
        auto& box = boxes[i];
        //std::cout << "Processing box " << i << " at position " << box.collider.body->getPosition() << "\n";
        if (!cData.hasMoreContacts())
        {
            
            return;
        }


        detector.boxAndHalfSpace(box.collider, groundPlane, &cData);
        //std::cout << "After detector call, contactsLeft: " << cData.contactsLeft << "\n";

    }

    
}