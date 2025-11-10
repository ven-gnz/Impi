#pragma once
#include "Scene.h"
#include "src/physics/RigidBody.h"
#include "src/physics/ForceGenerators.h"


class MobileScene : public Scene
{

	Vector3 centerPoint;

	Vector3 mobile1_initialPos;
	Vector3 mobile1_offset;
	Vector3 center_to_1offset;

	Vector3 mobile2_initialPos;
	Vector3 mobile2_offset;
	Vector3 center_to_2offset;

	RigidBody centerpiece;
	RigidBody attachment1;
	RigidBody attachment2;

	real defaultSpringConstant;
	real defaultRestLength;

	real restLength1;
	real restLength2;

	SphereMesh sphere_mesh;

public:

	Spring from_center_to_attach1;
	Spring from_center_to_attach2;
	Gravity scene_gravity;

	MobileScene(Camera &camera);

	virtual void onActivate() override;

	virtual void update(real dt) override;

	virtual void draw(Renderer& renderer, Camera& camera) override;


};