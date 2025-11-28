#pragma once
#include <src/scenes/Scene.h>
#include <src/rendering/assets/Mesh.h>
#include <src/physics/RigidBody_System/RigidBody.h>
#include <src/rendering/assets/RenderableRigidBody.h>
#include "src/physics/RigidBody_System/ForceGenerators.h"
#include <src/physics/RigidBody_System/CollisionDetector.h>




class BoxBoxScene : public Scene
{





	CubeMesh cubeMesh;

	Vector3 lastMousePos;

	std::vector<RenderableRigidBody> renderables;
	std::vector<Vector3> cubePositions;

	CollisionData cData;





public:

	Gravity scene_gravity;

	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;

	virtual void generateContacts();

};