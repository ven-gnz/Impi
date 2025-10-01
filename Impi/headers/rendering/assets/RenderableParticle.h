#pragma once
#include <glad/glad.h>
#include "particle.h"
#include "rendering/assets/SphereMesh.h"
#include <glm/glm.hpp>


class RenderableParticle : public Particle
{
public:
	unsigned int shaderProgram;
	SphereMesh* mesh = nullptr;
	float radius = 1.0f;

	void draw() const;
};