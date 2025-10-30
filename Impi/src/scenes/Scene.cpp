#include <src/scenes/Scene.h>

/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meillä selvästi on tulossa eri
	testiscenejä niin ehkä tällainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mitä tulee.
*/

Scene::Scene(std::string init_name,
	Camera& camera,
	const char* vertexPath,
	const char* fragmentPath,
	const char* geometryPath) 
	: name(init_name), camera(camera), shader(vertexPath,fragmentPath,geometryPath),
	groundShader("src/scenes/commons/shaders/grid.vert", "src/scenes/commons/shaders/grid.frag", nullptr)
{
	
	ViewUniform.view = camera.GetViewMatrix();
	ViewUniform.projection = camera.getProjection();
	ViewUniform.cameraPos = camera.getPosition();
	ViewUniform.padding = 0.0f;

	groundmesh_ptr = new PlaneMesh();
	groundmesh_ptr->createPlane();

	groundShader.use();

}

void Scene::update(float dt)  {}


void Scene::draw(Renderer& renderer, Camera& camera){ }

std::string Scene::getName() const
{
	return name;
}


void Scene::onMouseButton(GLFWwindow* window, int button, int action, int mods) {}
void Scene::onActivate() 
{
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

