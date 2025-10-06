#pragma once



class SphereParticle : public RenderableParticle
{
public:
	SphereMesh* mesh = nullptr;

	SphereParticle(Particle* physicParticle, SphereMesh* mesh, float r = 1.0f)
		: RenderableParticle(physicParticle,mesh,r)
	{
		
	}

};