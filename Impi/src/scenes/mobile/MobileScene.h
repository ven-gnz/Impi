#pragma once
#include "Scene.h"
#include "src/physics/RigidBody.h"
#include "src/physics/ForceGenerators.h"
#include "src/physics/ForceRegistry.h"
#include "rendering/assets/RenderableRigidBody.h"


class MobileScene : public Scene
{

	Vector3 centerPoint;

	Vector3 mobile1_initialPos;
	Vector3 mobile2_initialPos;

	RigidBody centerpiece;
	RigidBody attachment1;
	RigidBody attachment2;

	ForceRegistry registry;

	real defaultSpringConstant;
	real defaultRestLength;

	real restLength1;
	real restLength2;

	SphereMesh sphere_mesh;
	LineMesh att1;
	LineMesh att2;

	std::vector<RenderableRigidBody> renderables;

public:
	 // from centerpiece to attachment respective of num
	Spring* spring1;
	Spring* spring2;
	TorqueGenerator motor;
	Gravity scene_gravity;

	MobileScene(Camera &camera);

	virtual void onActivate() override;

	virtual void update(real dt) override;

	virtual void draw(Renderer& renderer, Camera& camera) override;


};