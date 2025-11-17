#pragma once
#include "scenes/Scene.h"
#include "physics/ParticleForceGenerators.h"
#include "rendering/assets/Mesh.h"
#include "physics/Particle.h"

class RopeScene : public Scene

{
	Vector3 cubePos;
	Vector3 spherePos;
	Vector3 lastMousePos;

	Particle sphere;
	Particle cube;

	Vector3 sphereStartingPos;

	real defaultSpringConstant;
	real defaultRestLength;

	real springConstant;
	real restLength;

	SphereMesh sphere_mesh;
	CubeMesh cube_mesh;
	LineMesh kick_magnitude;
	LineMesh spring_line;

	bool canKick;
	real kickTimer;
	float kickCD;



public :
	RopeScene(Camera& camera);

	ParticleAnchoredSpring from_cube_to_sphere;
	ParticleGravity scene_gravity;

	virtual void draw(Renderer& renderer, Camera& camera) override;
	virtual void update(real dt) override;
	virtual void onActivate() override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods);

	Vector3 screenToWorld(double xpos, double ypos,GLFWwindow* window, glm::mat4 view, glm::mat4 proj);
	void updateMouse(GLFWwindow* window, const Renderer& renderer) override;

};