#pragma once
#include "scenes/Scene.h"
#include "src/physics/Firework.cpp"

class FireWorkScene : public Scene
{
public:

	const static unsigned maxFireworks = 1024;

	Firework fireworks[maxFireworks];
	unsigned nextFirework;
	const static unsigned ruleCount = 9;
	FireworkRule rules[ruleCount];

	void createInitial(unsigned type, const Firework* parent = NULL);
	void createAdditional(unsigned type, unsigned number, const Firework* parent);
	FireWorkScene(Camera& camera);
	void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	void initFireworkRules();

	FireWorkScene(Camera& camera);

	void initFireWorkRules();

	void update(float dt) override;

	void draw() override;
};