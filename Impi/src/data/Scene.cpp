#include <data/Scene.h>


/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meill� selv�sti on tulossa eri
	testiscenej� niin ehk� t�llainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mit� tulee.
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