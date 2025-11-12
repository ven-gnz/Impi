#include "MobileScene.h"
#include "glm/glm.hpp"



MobileScene::MobileScene(Camera& camera)
    : Scene("Mobil_1",
        camera,
        "src/scenes/mobile/shaders/mobil.vert",
        "src/scenes/mobile/shaders/mobil.frag",
        nullptr),
        centerPoint(Vector3(0,0,0)),
        mobile1_initialPos(Vector3(-2,-1,0)),
        mobile1_offset(1,0,0),
        center_to_1offset(-1,0,0),
        mobile2_initialPos(Vector3(2,-1,0)),
        mobile2_offset(1,0,0),
        center_to_2offset(-1,0,0),
        defaultSpringConstant(15.5f),
        defaultRestLength(2),
        restLength1(defaultRestLength),
        restLength2(defaultRestLength),
        spring1(center_to_1offset,attachment1,mobile1_offset,defaultSpringConstant,defaultRestLength),
        spring2(center_to_2offset,attachment2,mobile2_offset,defaultSpringConstant,defaultRestLength)

{
    centerpiece->setPosition(centerPoint);
    attachment1->setPosition(mobile1_initialPos);
    attachment2->setPosition(mobile2_initialPos);

    sphere_mesh.createMesh(1.0f);
    sphere_mesh.uploadToGPU();
    spheremesh_ptr = &sphere_mesh;

}

void MobileScene::draw(Renderer& renderer, Camera& camera)
{
    renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());

    groundShader.use();
    glBindVertexArray(groundmesh_ptr->vao);
    groundmesh_ptr->draw();

    for (auto& renderable : renderables)
    {
        renderable.updateModelMatrix();
    }

    shader.use();


    glBindVertexArray(spheremesh_ptr->vao);
    for (auto& r : renderables)
    {
        shader.setMat4("model", r.model);
        r.mesh->draw();
    }

    glBindVertexArray(0);
    
}

void MobileScene::update(real dt) 
{
    centerpiece->clearAccumulators();
    attachment1->clearAccumulators();
    attachment2->clearAccumulators();

    registry.updateForces(dt);

    centerpiece->integrate(dt);
    attachment1->integrate(dt);
    attachment2->integrate(dt);
}

void MobileScene::onActivate()
{
    centerpiece->setOrientation(Quaternion(1, 0, 0, 0));
    centerpiece->setPosition(centerPoint);
    attachment1->setPosition(mobile1_initialPos);
    attachment2->setPosition(mobile2_initialPos);
    centerpiece->addTorque(Vector3(0, 2, 0));
}



