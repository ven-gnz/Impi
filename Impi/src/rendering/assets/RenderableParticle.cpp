#include "rendering/assets/RenderableParticle.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Vector3.h"

/*
Perinnällä mennään, ehkä tähän löytyy joku toimivampi ratkaisu myöhemmin.
*/

void RenderableParticle::draw(unsigned int shaderProgram) const
{

	glm::vec3 pos(position.x, position.y, position.z);

	glm::mat4 model(1.0f);

	model = glm::translate(model, pos)
		* glm::scale(glm::mat4(1.0f), glm::vec3(radius));

	int uni = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uni, 1, GL_FALSE, &model[0][0]);

	mesh->draw();
}