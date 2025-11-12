#include "MobileScene.h"


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
        from_centerpiece_to_attach1(center_to_1offset,attachment1,mobile1_offset,defaultSpringConstant,defaultRestLength),
        from_centerpiece_to_attach2(center_to_2offset,attachment2,mobile2_offset,defaultSpringConstant,defaultRestLength)

{
    centerpiece->setPosition(centerPoint);
    attachment1->setPosition(mobile1_initialPos);
    attachment2->setPosition(mobile2_initialPos);
}

void MobileScene::draw(Renderer& renderer, Camera& camera)
{

    
}

void MobileScene::update(real dt) 
{

}

void MobileScene::onActivate()
{
    centerpiece->setOrientation(Quaternion(1, 0, 0, 0));
    centerpiece->setPosition(centerPoint);
    attachment1->setPosition(mobile1_initialPos);
    attachment2->setPosition(mobile2_initialPos);
    
}



