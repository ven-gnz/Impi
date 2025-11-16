#pragma once
#include "src/physics/RigidBody.h"
#include "SphereMesh.h"
#include <glm/gtc/type_ptr.hpp>

using namespace Impi;
class RenderableRigidBody
{
public:
	RigidBody* body;
	SphereMesh* mesh;
	float radius = 1.0f;
	glm::mat4 model = glm::mat4(1.0f);


	RenderableRigidBody(RigidBody* p, SphereMesh* m, float r)
		: body(p), mesh(m), radius(r) {
	}


	void updateModelMatrix()
	{
		float mat[16];
		body->getGLTransform(mat);
		model = glm::make_mat4(mat);
	}
};