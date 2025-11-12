#pragma once
#include "Scene.h"
#include "src/physics/RigidBody.h"
#include "src/physics/ForceGenerators.h"
#include "src/physics/ForceRegistry.h"


class MobileScene : public Scene
{

	Vector3 centerPoint;

	Vector3 mobile1_initialPos;
	Vector3 mobile1_offset;
	Vector3 center_to_1offset;

	Vector3 mobile2_initialPos;
	Vector3 mobile2_offset;
	Vector3 center_to_2offset;

	RigidBody* centerpiece;
	RigidBody* attachment1;
	RigidBody* attachment2;

	ForceRegistry registry;

	real defaultSpringConstant;
	real defaultRestLength;

	real restLength1;
	real restLength2;

	SphereMesh sphere_mesh;

public:
	 // from centerpiece to attachment respective of num
	Spring spring1;
	Spring spring2;
	Gravity scene_gravity;

	MobileScene(Camera &camera);

	virtual void onActivate() override;

	virtual void update(real dt) override;

	virtual void draw(Renderer& renderer, Camera& camera) override;


};