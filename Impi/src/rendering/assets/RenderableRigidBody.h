#pragma once
#include "src/physics/RigidBody.h"
#include <glm/gtc/type_ptr.hpp>
#include <src/rendering/assets/Mesh.h>


using namespace Impi;

class RenderableRigidBody
{
public:
	RigidBody* body;
	Mesh* mesh;
	float radius;
	glm::vec3 scaler;
	glm::mat4 model = glm::mat4(1.0f);


	RenderableRigidBody(RigidBody* p, Mesh* m, float r, glm::vec3 s)
		: body(p), mesh(m), radius(r), scaler(s) {
	}


	void updateModelMatrix()
	{
		float mat[16];
		body->getGLTransform(mat);
		model = glm::scale(glm::make_mat4(mat), scaler);
	}
};