#pragma once
#include <scenes/Scene.h>
#include <opengl/Mesh.h>
#include <physics/RigidBody_System/RigidBody.h>
#include <opengl/RenderableRigidBody.h>
#include <math/random.h>



using namespace Impi;

/**
* Simple struct for this scene
*/
struct Box {

	CollisionBox collider;
	RigidBody body;
	CubeMesh* mesh_ptr = nullptr;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 scaler = glm::vec3(1.0f);
	Vector3 position;
	void updateModelMatrix();
	Vector3 color;

};


class BoxBoxScene : public Scene
{


	CubeMesh cubeMesh;
	Vector3 lastMousePos;
	Random random;

	std::vector<RenderableRigidBody> renderables;
	std::vector<Vector3> cubePositions;
	std::vector<Box> boxes;

	unsigned int NUM_BOXES = 150;


public:

	Gravity scene_gravity;

	BoxBoxScene(Camera &camera);

	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;


};