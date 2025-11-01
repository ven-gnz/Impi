#pragma once
#include <vector>
#include <Particle.h>
#include <ParticleLinks.h>

class Cloth
{

	int particles_width;
	int particles_height;

	std::vector<Particle> particles;
	std::vector<ParticleCable> constraints;


public:
	Cloth();
};