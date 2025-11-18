#pragma once
#include "scenes/Scene.h"
#include "src/physics/Objects/Firework.h"
#include <src/math/random.h>

class FireWorkScene : public Scene
{
public:

	struct RenderableFirework {
		glm::vec4 pos;
		glm::vec4 color;
	};

	const size_t maxFireworks = 2048;
	std::vector<Firework> fireworks;
	size_t nextFirework;
	Random simplerandom;

	std::vector<RenderableFirework> renderableFireworks;
	GLuint fireworkscene_VAO = 0;
	GLuint fireworkscene_VBO = 0;


	const static unsigned ruleCount = 9;
	// FireworkRule rules[ruleCount];

	std::vector<FireworkRule> rules;

	FireWorkScene(Camera& camera);

	void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	void initFireWorkRules();

	/** Dispatches the given number of fireworks from the given parent. */
	void create(unsigned type, unsigned count, const Firework* parent);

	/** Dispatches a firework from the origin. */
	void create(unsigned type, const Firework* parent = NULL);

	void onActivate() override;

	void update(real dt) override;

	void init_datastream();

	void fill_renderbuffer();
	void upstream_renderbuffer();

	glm::vec4 getCol(unsigned type);

	void draw(Renderer& renderer, Camera& camera) override;
};