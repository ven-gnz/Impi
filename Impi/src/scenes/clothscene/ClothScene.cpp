#include <src/scenes/clothscene/ClothScene.h>



ClothScene::ClothScene(Camera& camera, real clothWidth, real clothHeight)
	: Scene("ClothScene",
		camera,
		"src/scenes/clothscene/cloth.vert",
		"src/scene/clothscene/cloth.frag",
		nullptr), 
		clothWidth(clothWidth), 
		clothHeight(clothHeight),
		cloth(clothWidth, clothHeight, 55, 45, Vector3(-15, 10, 0)),
		windForce(2,3,0)
{
	std::cout << "Constructor reached" << std::endl;
	shader.use();
	renderableVertices.reserve(sizeof(RenderableClothVertex) * cloth.getVertices().size());
	indices = calculate_indices(cloth);
	init_datastream();
}


std::vector<GLuint> ClothScene::calculate_indices(const VerletCloth& cloth)
{

	std::vector<GLuint> indices;
	indices.reserve((cloth.getWidthCount() - 1) * (cloth.getHeightCount() - 1) * 6);


	cloth.forEachTriangle([&](const ClothParticle* p1, const ClothParticle* p2, const ClothParticle* p3)
		{

			int i1 = cloth.getParticleIndex(p1);
			int i2 = cloth.getParticleIndex(p2);
			int i3 = cloth.getParticleIndex(p3);

			indices.push_back(static_cast<GLuint>(i1));
			indices.push_back(static_cast<GLuint>(i2));
			indices.push_back(static_cast<GLuint>(i3));
		});

	return indices;
}

void ClothScene::init_datastream()
{
	renderableVertices.clear();

	glGenVertexArrays(1, &clothVAO);
	glGenBuffers(1, &clothVBO);
	glGenBuffers(1, &clothEBO);

	glBindVertexArray(clothVAO);
	glBindBuffer(GL_ARRAY_BUFFER, clothVBO);

	glBufferData(GL_ARRAY_BUFFER, cloth.getVertices().size() * sizeof(RenderableClothVertex), nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, clothEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RenderableClothVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(RenderableClothVertex), (void*)(sizeof(glm::vec3)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(RenderableClothVertex), (void*)(2 * sizeof(glm::vec3)));

	glBindVertexArray(0);
}





void ClothScene::fill_renderbuffer()
{

	const auto& parts = cloth.getParticles();
	const auto  normals = cloth.getNormals();

	renderableVertices.resize(cloth.getParticles().size());

	float minX = cloth.minX();
	float maxX = cloth.maxX();
	float rangeX = std::max(0.001f, maxX - minX);

	for (size_t i = 0; i < cloth.getParticles().size(); i++)
	{

		const ClothParticle& p = parts[i];

		renderableVertices[i].pos = glm::vec3(p.getPosition().x,
			p.getPosition().y,
			p.getPosition().z);

		renderableVertices[i].norm = glm::vec3(normals[i].x,
			normals[i].y,
			normals[i].z);
		
		float t = (p.getPosition().x - minX) / rangeX;
		renderableVertices[i].col = glm::vec3(1.0f, t, t);
	}

}

void ClothScene::upstream_renderbuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, clothVBO);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		0,
		renderableVertices.size() * sizeof(RenderableClothVertex),
		renderableVertices.data()
	);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void ClothScene::update(real dt)
{
	cloth.addDottedForce(windForce);
	cloth.addForceToCloth(Vector3(0, -9.8, 0));
	cloth.updateClothParticles(dt);
}

void ClothScene::draw(Renderer& renderer, Camera& camera)
{
	shader.use();
	renderer.setUniform(camera.GetViewMatrix(), camera.getProjection(), camera.getPosition());
	
	fill_renderbuffer();
	upstream_renderbuffer();

	glBindVertexArray(clothVAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

}