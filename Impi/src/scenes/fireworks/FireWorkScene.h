#pragma once
#include "scenes/Scene.h"
#include "src/physics/Firework.h"
#include <src/math/random.h>

class FireWorkScene : public Scene
{
public:

	const size_t maxFireworks = 1024;
	std::vector<Firework> fireworks;
	size_t nextFirework;
	Random simplerandom;


	unsigned nextFirework;
	const static unsigned ruleCount = 9;
	FireworkRule rules[ruleCount];

	
	FireWorkScene(Camera& camera);
	void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	void initFireWorkRules();

	/** Dispatches the given number of fireworks from the given parent. */
	void create(unsigned type, unsigned count, const Firework* parent);

	/** Dispatches a firework from the origin. */
	void create(unsigned type, const Firework* parent = NULL);

	void update(real dt) override;

	void draw() override;
};