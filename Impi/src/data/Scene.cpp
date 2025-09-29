#include <data/Scene.h>


/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meillä selvästi on tulossa eri
	testiscenejä niin ehkä tällainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mitä tulee.
*/

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