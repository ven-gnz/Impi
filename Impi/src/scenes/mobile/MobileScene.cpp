#include "MobileScene.h"


MobileScene::MobileScene(Camera& camera)
    : Scene("Mobil_1",
        camera,
        "src/scenes/mobile/shaders/mobil.vert",
        "src/scenes/mobile/shaders/mobil.frag",
        nullptr)
    :   centerPoint(Vector3(0,0,0),
        mobile1_initialPos(-2,-1,0),
        mobile1_offset(1,0,0),
        center_to_1offset(-1,0,0)
        mobile2_initialPos(2,-1,0),
        mobile2_offset(1,0,0),
        center_to_2offset(-1,0,0)
        defaultSpringConstant(15.5f),
        defaultRestLength(2),
        restLength1(defaultRestLength),
        restLength2(defaultRestLength),
        from_center_to_attach1(center_to_1offset,attachment1,defaultSpringConstant,defaultRestLength),
        from_center_to_attach2(center_to_2offset,attachment2,defaultSpringConstant,defaultRestLength)

{

}



