#pragma once
#include <rendering/assets/RenderableParticle.h>
// Luokka erikoistaa renderableparticlen jahka sinne asti p‰‰st‰‰n.

class SphereParticle : public RenderableParticle
{
public:
	SphereMesh* mesh = nullptr;

	SphereParticle(Particle* physicParticle, SphereMesh* mesh, float r = 1.0f)
		: RenderableParticle(physicParticle,mesh,r)
	{	}

};