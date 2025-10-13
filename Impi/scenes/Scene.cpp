#include "Scene.h"

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



	
	glBindVertexArray(spheremesh_ptr->vao);
	for (auto& r : renderables)
	{
		shader.setMat4("model", r.model);
		r.mesh->draw();
	}

	glBindVertexArray(0);
}

std::string Scene::getName() const
{
	return name;
}

void Scene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

