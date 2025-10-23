#pragma once
#include "scenes/Scene.h"
#include "src/physics/Firework.cpp"

class FireWorkScene : public Scene
{
public:
	FireWorkScene(Camera& camera);
	void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	void spawnFireWorks();
};