#pragma once
#include <glad/glad.h>
#include "physics/Particle.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


// 6.10. uusi yritys : en halua luoda objekteja, vaan haluan että fysiikkasimun renderöintiin käytetään
// jo olemassa olevan partikkelin attribuutteja...

class RenderableParticle
{
public:
	Particle* physicalParticle;
	Mesh* mesh;
	float radius = 1.0f;
	glm::mat4 model = glm::mat4(1.0f);

	RenderableParticle(Particle* p, Mesh* m, float r = 1.0f)
		: physicalParticle(p), mesh(m), radius(r) { }


	void updateModelMatrix()
	{
		Vector3 p = physicalParticle->getPosition();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(p.x, p.y, p.z))
			* glm::scale(glm::mat4(1.0f), glm::vec3(radius));
	}
};