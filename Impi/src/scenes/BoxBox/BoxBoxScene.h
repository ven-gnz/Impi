#pragma once
#include <src/scenes/Scene.h>
#include <src/rendering/assets/Mesh.h>
#include <src/physics/RigidBody_System/RigidBody.h>
#include <src/rendering/assets/RenderableRigidBody.h>
#include "src/physics/RigidBody_System/ForceGenerators.h"
#include <src/physics/RigidBody_System/CollisionDetector.h>
#include <src/physics/RigidBody_System/Contact.h>
#include <src/physics/RigidBody_System/ForceRegistry.h>



using namespace Impi;

/**
* Simple struct for this scene
*/
struct Box {

	CollisionBox collider;
	RigidBody body;
	CubeMesh* mesh_ptr;
	glm::mat4 model;
	glm::vec3 scaler;
	void updateModelMatrix();

};


class BoxBoxScene : public Scene
{



	CubeMesh cubeMesh;

	Vector3 lastMousePos;

	std::vector<RigidBody> ammoRigidBodies;
	std::vector<RigidBody> boxwallRigidBodies;

	std::vector<Box> boxes;


	std::vector<RenderableRigidBody> renderables;
	std::vector<Vector3> cubePositions;

	const static unsigned maxContacts = 256;
	Contact contacts[maxContacts];
	CollisionData cData;

	CollisionDetector detector;

	CollisionPlane groundPlane;

	ForceRegistry registry;


public:

	Gravity scene_gravity;

	BoxBoxScene(Camera &camera);

	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;

	virtual void generateContacts();

};