// stuff I want to keep here

#include <data/Scene.h>
#include <rendering/assets/RenderableParticle.h>

// jaaa asioita joita en halua pit‰‰ t‰‰ll‰ -> per scene asiaa, jotenkin vied‰‰n omaan "ballisticSceneen" pian
#include "rendering/assets/SphereMesh.h"
SphereMesh particleMesh;

/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meill‰ selv‰sti on tulossa eri
	testiscenej‰ niin ehk‰ t‰llainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mit‰ tulee.
*/

Scene::Scene(std::string name)
{
	name = name;
}

void Scene::update(float dt)
{
	for (auto& particle : particles)
	{
		particle.integrate(dt);
	}
}

void Scene::draw(unsigned int shaderProgram) const
{
	for (auto& particle : particles)
	{
		particle.draw(shaderProgram);
	}
}

std::string Scene::getName() const
{
	return name;
}

void Scene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		RenderableParticle p;
		p.mesh = &particleMesh;
		p.setPosition(Vector3(0, 5, 0));
		p.setVelocity(Vector3(5, 5, 0));

		p.radius = 0.5f;
		particles.push_back(p);
	}
}

