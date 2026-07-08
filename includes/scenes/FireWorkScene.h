#pragma once
#include <scenes/Scene.h>
#include <physics/Objects/Firework.h>
#include <math/random.h>

class FireWorkScene : public Scene
{
public:

	struct RenderableFirework {
		glm::vec4 pos;
		glm::vec4 color;
	};

	std::vector<RenderableFirework> renderableFireworks;
	GLuint fireworkscene_VAO = 0;
	GLuint fireworkscene_VBO = 0;


	const static unsigned ruleCount = 9;
	// FireworkRule rules[ruleCount];

	std::vector<FireworkRule> rules;

	FireWorkScene(Camera& camera);

	void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	void onActivate() override;

	void update(real dt) override;

	void draw(Renderer& renderer, Camera& camera) override;

	void init_datastream();
	void fill_renderbuffer();
	void upstream_renderbuffer();
	glm::vec4 getCol(unsigned type);
	unsigned int maxFireworks = 4096;
};