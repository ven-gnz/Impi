#include "MobileScene.h"
#include "glm/glm.hpp"
#include "src/math/Matrix.h"


MobileScene::MobileScene(Camera& camera)
    : Scene("Mobil_1",
        camera,
        "src/scenes/mobile/shaders/mobile.vert",
        "src/scenes/mobile/shaders/mobile.frag",
        nullptr),
        centerPoint(Vector3(0,7,0)),
        mobile1_initialPos(Vector3(-4,2,0)),
        mobile2_initialPos(Vector3(4,2,0)),
        defaultSpringConstant(30.5f),
        defaultRestLength(1),
        restLength1(defaultRestLength),
        restLength2(defaultRestLength),
        centerpiece(),
        attachment1(),
        attachment2(),
        registry(),
        scene_gravity(Gravity()),
        motor()

{

    Matrix3 i = Matrix3::identity();
   
    centerpiece.setOrientation(Quaternion(1, 0, 0, 0));
    centerpiece.setPosition(centerPoint);
    centerpiece.setMass(25.0f);
    centerpiece.setInertiaTensor(i);
    centerpiece.setAngularDamping(0.2f);
    centerpiece.calculateDerivedData();

    attachment1.setOrientation(Quaternion(1, 0, 0, 0));
    attachment1.setPosition(mobile1_initialPos);
    attachment1.setInertiaTensor(i);
    attachment1.setMass(2.5f);
    attachment1.setAngularDamping(0.8f);
    attachment1.calculateDerivedData(); 

    attachment2.setOrientation(Quaternion(1, 0, 0, 0));
    attachment2.setPosition(mobile2_initialPos);
    attachment2.setInertiaTensor(i);
    attachment2.setMass(2.5f);
    attachment2.setAngularDamping(0.8f);
    attachment2.calculateDerivedData();

    sphere_mesh.createMesh(1.0f);
    sphere_mesh.uploadToGPU();
    spheremesh_ptr = &sphere_mesh;
    motor.setTorque(Vector3(0, 5, 0));

      
    Vector3 o1(-1.0f, 0.0f, 0.0f); // local space offsets
    Vector3 o2(1.0f, 0.0f, 0.0f);
    Vector3 zero(0.0f, 0.0f, 0.0f);

    spring1 = new Spring(o1, &attachment1, zero, defaultSpringConstant, defaultRestLength);
    spring2 = new Spring(o2, &attachment2, zero, defaultSpringConstant, defaultRestLength);

    //auto& m = centerpiece.transformMatrix;
    //for (int i = 0; i < 16; ++i) std::cout << m.data[i] << " ";

    //Vector3 start1 = spring1->getAnchorWorldB(&attachment1);
    //Vector3 end1 = spring1->getAnchorWorldA(&centerpiece);
    //std::cout << "Spring1 anchors: " << start1.x << "," << start1.y << "," << start1.z
    //    << " -> " << end1.x << "," << end1.y << "," << end1.z << std::endl;

    //Vector3 start2 = spring2->getAnchorWorldB(&attachment2);
    //Vector3 end2 = spring2->getAnchorWorldA(&centerpiece);
    //std::cout << "Spring2 anchors: " << start2.x << "," << start2.y << "," << start2.z
    //    << " -> " << end2.x << "," << end2.y << "," << end2.z << std::endl;

    shader.use();
    shader.setVec3("color", glm::vec3(0.9, 0.9, 0.9));

    registry.add(&attachment1, spring1);
    registry.add(&attachment2, spring2);
   
    registry.add(&centerpiece, &motor);

    registry.add(&attachment1, &scene_gravity);
    registry.add(&attachment2, &scene_gravity);
    // AND add force registrations to the other direction of the spring to honor newtons third.
    registry.add(&centerpiece, spring1);
    registry.add(&centerpiece, spring2);


    renderables.push_back(RenderableRigidBody(&centerpiece, spheremesh_ptr, 1.0));
    renderables.push_back(RenderableRigidBody(&attachment1, spheremesh_ptr, 1.0));
    renderables.push_back(RenderableRigidBody(&attachment2, spheremesh_ptr, 1.0));

    //std::cout << "centerpiece invMass = " << centerpiece.getMass() << std::endl;

    //std::cout << "InverseInertiaTensorWorld: "
    //    << centerpiece.inverseInertiaTensorWorld.data[0] << " "
    //    << centerpiece.inverseInertiaTensorWorld.data[4] << " "
    //    << centerpiece.inverseInertiaTensorWorld.data[8] << std::endl;

    lineShader.use();
    att1.uploadToGPU();
    att2.uploadToGPU();
}

void MobileScene::draw(Renderer& renderer, Camera& camera)
{
    renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());

    groundShader.use();
    glBindVertexArray(groundmesh_ptr->vao);
    groundmesh_ptr->draw();

    shader.use();
   
    glBindVertexArray(spheremesh_ptr->vao);
    for (auto& r : renderables)
    {
        r.updateModelMatrix();
        shader.setMat4("model", r.model);
        r.mesh->draw();
    }

    lineShader.use();

    
    Vector3 a1 = spring1->getAnchorWorldA(&centerpiece);
    Vector3 b1 = spring1->getAnchorWorldB();               // attachment 

    att1.setPoints(
        glm::vec3(a1.x, a1.y, a1.z),
        glm::vec3(b1.x, b1.y, b1.z)
    );
    att1.uploadToGPU();
    att1.draw();

    Vector3 a2 = spring2->getAnchorWorldA(&centerpiece);   
    Vector3 b2 = spring2->getAnchorWorldB();               // attachment

    att1.setPoints(
        glm::vec3(a2.x, a2.y, a2.z),
        glm::vec3(b2.x, b2.y, b2.z)
    );
    att1.uploadToGPU();
    att1.draw();

    glBindVertexArray(0);
    
}

void MobileScene::update(real dt) 
{

    registry.updateForces(dt);

    Vector3 accumulatedTorque = centerpiece.torqueAccum;
    std::cout << "Centerpiece accumulated torque: "
        << accumulatedTorque.x << ", "
        << accumulatedTorque.y << ", "
        << accumulatedTorque.z << std::endl;

    centerpiece.integrate(dt);
    attachment1.integrate(dt);
    attachment2.integrate(dt);

    


    Vector3 angVel = centerpiece.getAngularVelocity();
    std::cout << "Angular velocity: "
        << angVel.x << ", "
        << angVel.y << ", "
        << angVel.z << std::endl;


}

void MobileScene::onActivate()
{
    Scene::onActivate();
    
    camera.Position = camera.defaultPos+ glm::vec3(0, 0, 12);
    centerpiece.setAngularVelocity(Vector3(0, 0, 0));
   

}



