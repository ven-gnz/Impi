#include <src/scenes/Scene.h>

/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meillä selvästi on tulossa eri
	testiscenejä niin ehkä tällainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mitä tulee.
*/

Scene::Scene(std::string init_name,
	const char* vertexPath,
	const char* fragmentPath,
	const char* geometryPath) 
	: name(init_name), shader(vertexPath,fragmentPath,geometryPath),
	groundShader("src/scenes/commons/shaders/grid.vert", "src/scenes/commons/shaders/grid.frag", nullptr)
{
	groundmesh_ptr = new PlaneMesh();
	groundmesh_ptr->createPlane(10.f, -0.25);

	initUBO();
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


void Scene::draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cameraPos) const
{

	updateUBO(view, projection, cameraPos);
	view_UBO_Debug_Data();

	groundShader.use();
	groundmesh_ptr->draw();

	/*
	
	


	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	
	glBindVertexArray(spheremesh_ptr->vao);
	for (auto& r : renderables)
	{
		shader.setMat4("model", r.model);
		r.mesh->draw();
	}
	*/

	glBindVertexArray(0);
}

std::string Scene::getName() const
{
	return name;
}

void Scene::initUBO() {
	glGenBuffers(1, &viewUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewUniforms), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, viewUBO);
}

void Scene::updateUBO(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos) const {

	ViewUniforms data;
	data.view = view;
	data.projection = projection;
	data.cameraPos = cameraPos;
	data.padding = 0.0f;

	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ViewUniforms), &data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void Scene::view_UBO_Debug_Data() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	ViewUniforms* ptr = (ViewUniforms*)glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_ONLY);
	if (ptr) {
		std::cout << "=== view ===" << std::endl;
		for (int col = 0; col < 4; ++col) {
			for (int row = 0; row < 4; ++row) {
				std::cout << "view[" << row << "][" << col << "] = " << ptr->view[col][row] << std::endl;
			}
		}

		std::cout << "=== projection ===" << std::endl;
		for (int col = 0; col < 4; ++col) {
			for (int row = 0; row < 4; ++row) {
				std::cout << "projection[" << row << "][" << col << "] = " << ptr->projection[col][row] << std::endl;
			}
		}

		std::cout << "=== camera position ===" << std::endl;
		std::cout << "cameraPos.x = " << ptr->cameraPos.x << std::endl;
		std::cout << "cameraPos.y = " << ptr->cameraPos.y << std::endl;
		std::cout << "cameraPos.z = " << ptr->cameraPos.z << std::endl;

		glUnmapBuffer(GL_UNIFORM_BUFFER);
	}
	else {
		std::cerr << "Failed to map UBO!" << std::endl;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Scene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

