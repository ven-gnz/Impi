#pragma once
#include <vector>
#include <Particle.h>
#include <ParticleLinks.h>
#include <Constraint.h>

class VerletCloth
{

	int particles_width;
	int particles_height;

	const int constraint_iterations = 10;

	std::vector<ClothParticle> particles;
	std::vector<Constraint> constraints;


public:
	VerletCloth(real width, real height, int num_particles_width, int num_particles_height);

	ClothParticle* getParticle(int x, int y);
	void addToConstraints(ClothParticle* p1, ClothParticle* p2);

	Vector3 getTriangleNormal(ClothParticle* p1, ClothParticle* p2, ClothParticle* p3);

	void drawTriangle(ClothParticle* p1, ClothParticle* p2, ClothParticle* p3, const Vector3 color);
	void addForcePerTriangle();

	void updateClothParticles();


};