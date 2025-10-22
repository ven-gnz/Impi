#include <src/scenes/Scene.h>

/*
	Pyrkimys formalisoida RR kurssilla vastaan tullut "Scene" ajatus. Nyt kun meillä selvästi on tulossa eri
	testiscenejä niin ehkä tällainen tarvitaan. Pikkuhiljaa iteroidaan, katsotaan mitä tulee.
*/

Scene::Scene(std::string init_name,
	Camera camera,
	const char* vertexPath,
	const char* fragmentPath,
	const char* geometryPath) 
	: name(init_name), shader(vertexPath,fragmentPath,geometryPath),
	groundShader("src/scenes/commons/shaders/grid.vert", "src/scenes/commons/shaders/grid.frag", nullptr)
{

	ViewUniform.view = camera.GetViewMatrix();
	// ViewUniform.projection = glm::lookAt();
	ViewUniform.cameraPos = camera.getPosition();
	ViewUniform.padding = 0.0f;

	groundmesh_ptr = new PlaneMesh();
	groundmesh_ptr->createPlane();

	initUBO();
	groundShader.use();
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

void Scene::updateViewUniform(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos) {
	ViewUniform.view = view;
	ViewUniform.projection = projection;
	ViewUniform.cameraPos = cameraPos;
	ViewUniform.padding = 0.0f;
}

void Scene::upstreamViewUniform() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ViewUniform_VPC), &ViewUniform);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void Scene::draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos)
{

	updateViewUniform(view, projection, cameraPos);
	upstreamViewUniform();
	view_UBO_Debug_Data();

	groundShader.use();
	glBindVertexArray(groundmesh_ptr->vao);
	groundmesh_ptr->draw();
	

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

void Scene::initUBO() {


	glGenBuffers(1, &viewUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ViewUniform), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, viewUBO);

	GLuint blockIndex = glGetUniformBlockIndex(groundShader.ID, "ViewUniforms");

	if (blockIndex != GL_INVALID_INDEX) {
		glUniformBlockBinding(groundShader.ID, blockIndex, 0);
	}
	else {
		std::cerr << "[WARN] ViewUniforms block not found in grid shader!\n";
	}

}

void Scene::updateUBO(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos) const {

	glBindBuffer(GL_UNIFORM_BUFFER, viewUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(ViewUniform_VPC), &ViewUniform);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void Scene::view_UBO_Debug_Data() const
{
	std::cout << "=== view ===" << std::endl;
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			std::cout << "view[" << row << "][" << col << "] = "
				<< ViewUniform.view[col][row] << std::endl;
		}
	}

	std::cout << "=== projection ===" << std::endl;
	for (int col = 0; col < 4; ++col) {
		for (int row = 0; row < 4; ++row) {
			std::cout << "projection[" << row << "][" << col << "] = "
				<< ViewUniform.projection[col][row] << std::endl;
		}
	}

	std::cout << "=== camera position ===" << std::endl;
	std::cout << "cameraPos.x = " << ViewUniform.cameraPos.x << std::endl;
	std::cout << "cameraPos.y = " << ViewUniform.cameraPos.y << std::endl;
	std::cout << "cameraPos.z = " << ViewUniform.cameraPos.z << std::endl;
}

void Scene::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

