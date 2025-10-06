#include "Scene.h"
#include <rendering/assets/RenderableParticle.h>


/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meillä selvästi on tulossa eri
	testiscenejä niin ehkä tällainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mitä tulee.
*/

Scene::Scene(std::string init_name,
	const char* vertexPath,
	const char* fragmentPath,
	const char* geometryPath) 
	: name(init_name), shader(vertexPath,fragmentPath,geometryPath)
{
}

void Scene::update(float dt)
{
	for (auto& particle : particles)
	{
		particle.integrate(dt);
	}

	for (auto& renderable : renderables)
	{
		renderable.updateModelMatrix();
	}
}

void Scene::draw(const glm::mat4& projection, const glm::mat4& view) const
{
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	glBindVertexArray(scenemesh->vao);

	for (auto& r : renderables)
	{
		shader.setMat4("model", r.model);
		if (r.mesh)
		{
			r.mesh->draw();
		}
	}
}

std::string Scene::getName() const
{
	return name;
}

void Scene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	// ballistics, spawn a renderable particle on mouse click. Wonder if well keep this...
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Particle p;
		p.setPosition(Vector3(0, 5, 0));
		p.setVelocity(Vector3(5, 5, 0));
		particles.push_back(p);
		Particle* physics_ptr = &particles.back();
		renderables.push_back(RenderableParticle(physics_ptr, &scenemesh, 1.0f));
	}
}

