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
        mobile1_offset(1,0,0),
        center_to_1offset(-1,0,0),
        mobile2_initialPos(Vector3(4,2,0)),
        mobile2_offset(1,0,0),
        center_to_2offset(-1,0,0),
        defaultSpringConstant(30.5f),
        defaultRestLength(1),
        restLength1(defaultRestLength),
        restLength2(defaultRestLength),
        centerpiece(),
        attachment1(),
        attachment2(),
        spring1(center_to_1offset,&centerpiece,mobile1_offset,defaultSpringConstant,defaultRestLength),
        spring2(center_to_2offset,&centerpiece,mobile2_offset,defaultSpringConstant,defaultRestLength),
        registry(),
        scene_gravity(Gravity()),
        motor()

{

    Matrix3 i = Matrix3::identity();
   
    centerpiece.setOrientation(Quaternion(1, 0, 0, 0));
    centerpiece.setPosition(centerPoint);
    centerpiece.setMass(25.0f);
    centerpiece.setInertiaTensor(i);
    centerpiece.setAngularDamping(0.8f);
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
    motor.setTorque(Vector3(0, 1, 0));

    registry.add(&attachment1, &spring1);
    registry.add(&attachment1, &scene_gravity);
    registry.add(&attachment2, &spring2);
    registry.add(&attachment2, &scene_gravity);
    registry.add(&centerpiece, &motor);

    renderables.push_back(RenderableRigidBody(&centerpiece, spheremesh_ptr, 1.0));
    renderables.push_back(RenderableRigidBody(&attachment1, spheremesh_ptr, 1.0));
    renderables.push_back(RenderableRigidBody(&attachment2, spheremesh_ptr, 1.0));

    std::cout << "centerpiece invMass = " << centerpiece.getMass() << std::endl;

    std::cout << "InverseInertiaTensorWorld: "
        << centerpiece.inverseInertiaTensorWorld.data[0] << " "
        << centerpiece.inverseInertiaTensorWorld.data[4] << " "
        << centerpiece.inverseInertiaTensorWorld.data[8] << std::endl;
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

    glBindVertexArray(0);
    
}

void MobileScene::update(real dt) 
{
    Quaternion orientation = centerpiece.getOrientation();
    //std::cout << "centerpiece i" << orientation.i << std::endl;
    //std::cout << "centerpiece j" << orientation.j << std::endl;
    //std::cout << "centerpiece r" << orientation.k << std::endl;
    //std::cout << "centerpiece r" << orientation.r << std::endl;

    //Vector3 pos = centerpiece.getPosition();
    //std::cout << "Position: x=" << pos.x
    //    << " y=" << pos.y
    //    << " z=" << pos.z << std::endl;

    //Vector3 pos1 = attachment1.getPosition();
    //Vector3 pos2 = attachment2.getPosition();

    //std::cout << "--- Attachment1 --- x=" << pos1.x
    //    << " y=" << pos1.y
    //    << " z=" << pos1.z << std::endl;

    //std::cout << "--- Attachment2 --- x=" << pos2.x
    //    << " y=" << pos2.y
    //    << " z=" << pos2.z << std::endl;

    registry.updateForces(dt);

    std::cout << "Attachment1 forceAccum: " << attachment1.forceAccum.x << ", "
        << attachment1.forceAccum.y << ", "
        << attachment1.forceAccum.z << std::endl;

    centerpiece.integrate(dt);
    attachment1.integrate(dt);
    attachment2.integrate(dt);

    Vector3 av = centerpiece.getRotation();
    Vector3 lv1 = attachment1.getVelocity();
    Vector3 lv2 = attachment2.getVelocity();

    std::cout << "AngularVel: " << av.x << "," << av.y << "," << av.z << std::endl;
    std::cout << "Attachment velocities: " << lv1.x << "," << lv1.y << "," << lv1.z
        << " | " << lv2.x << "," << lv2.y << "," << lv2.z << std::endl;

    //Vector3 vel = centerpiece.getVelocity();
    //Vector3 angVel = centerpiece.getAngularVelocity();
    //std::cout << "Linear velocity: x=" << vel.x << " y=" << vel.y << " z=" << vel.z << std::endl;
    //std::cout << "Angular velocity: x=" << angVel.x << " y=" << angVel.y << " z=" << angVel.z << std::endl;

}

void MobileScene::onActivate()
{
    Scene::onActivate();
    
    camera.Position = camera.defaultPos+ glm::vec3(0, 0, 12);
    centerpiece.setAngularVelocity(Vector3(0, 2, 0));
}



