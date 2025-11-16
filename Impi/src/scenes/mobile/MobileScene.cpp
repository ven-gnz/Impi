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
        defaultSpringConstant(10.0f),
        defaultRestLength(5.8),
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
    centerpiece.setMass(2.5f);
    centerpiece.setInertiaTensor(i);
    centerpiece.setLinearDamping(0.2f);
    centerpiece.calculateDerivedData();

    attachment1.setOrientation(Quaternion(1, 0, 0, 0));
    attachment1.setPosition(mobile1_initialPos);
    attachment1.setInertiaTensor(i);
    attachment1.setMass(2.0f);
    attachment1.setLinearDamping(0.1f);
    attachment1.calculateDerivedData(); 

    attachment2.setOrientation(Quaternion(1, 0, 0, 0));
    attachment2.setPosition(mobile2_initialPos);
    attachment2.setInertiaTensor(i);
    attachment2.setMass(2.0f);
    attachment2.setLinearDamping(0.1f);
    attachment2.calculateDerivedData();

    sphere_mesh.createMesh(1.0f);
    sphere_mesh.uploadToGPU();
    spheremesh_ptr = &sphere_mesh;
 
    Vector3 o1(-1.0f, 0.0f, 0.0f); // local space offsets
    Vector3 o2(1.0f, 0.0f, 0.0f);
    Vector3 zero(0.0f, 0.0f, 0.0f);

    spring1 = new Spring(o1, &centerpiece, zero, defaultSpringConstant, restLength1);
    spring2 = new Spring(o2, &centerpiece, zero, defaultSpringConstant, restLength2);

    shader.use();
    shader.setVec3("color", glm::vec3(0.9, 0.9, 0.9));

    motor.setTorque(Vector3(0, 200, 0));

    registry.add(&attachment1, spring1);
    registry.add(&attachment2, spring2);

    registry.add(&attachment1, &scene_gravity);
    registry.add(&attachment2, &scene_gravity);
    registry.add(&centerpiece, &motor);

    renderables.push_back(RenderableRigidBody(&centerpiece, spheremesh_ptr, 2.0));
    renderables.push_back(RenderableRigidBody(&attachment1, spheremesh_ptr, 1.0));
    renderables.push_back(RenderableRigidBody(&attachment2, spheremesh_ptr, 1.0));

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

    att2.setPoints(
        glm::vec3(a2.x, a2.y, a2.z),
        glm::vec3(b2.x, b2.y, b2.z)
    );
    att2.uploadToGPU();
    att2.draw();

    glBindVertexArray(0);
    
}

void MobileScene::update(real dt) 
{

    registry.updateForces(dt);

    //printf("before:  mass=%f forceAccum.y=%f vel.y=%f pos.y=%f\n",
    //    attachment1.getMass(),
    //    attachment1.forceAccum.y,
    //    attachment1.getVelocity().y,
    //    attachment1.getPosition().y);

    attachment1.setVelocity(Vector3(0, -2, 0));
    centerpiece.integrate(dt);
    attachment1.integrate(dt);
    attachment2.integrate(dt);

    //printf("after:  mass=%f forceAccum.y=%f vel.y=%f pos.y=%f\n",
    //    attachment1.getMass(),
    //    attachment1.forceAccum.y,
    //    attachment1.getVelocity().y,
    //    attachment1.getPosition().y);

   




}

void MobileScene::onActivate()
{
    Scene::onActivate();
    camera.Position = camera.defaultPos+ glm::vec3(0, 0, 12);
    
   

}



