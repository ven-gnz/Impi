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

	/**
	* Get the particle index on the flat particles array
	*/
	int getParticleIndex(ClothParticle* p);

public:
	VerletCloth(real width, real height, int num_particles_width, int num_particles_height);

	ClothParticle* getParticle(int x, int y);
	void addToConstraints(ClothParticle* p1, ClothParticle* p2);

	Vector3 getTriangleNormal(ClothParticle* p1, ClothParticle* p2, ClothParticle* p3);

	void updateClothParticles(real dt);


	/**
	* Adds a per triangle force for the cloth
	*/
	void addDottedForce(const Vector3& forceDirection);

	/**
	* Adds a force acting on all particles separately
	*/
	void addForceToCloth(Vector3 force);

	

	std::vector<Vector3> getVertices() const;
	std::vector<Vector3> getNormals();

	// My first template (:

	/**
	 * Convenience function that iterates over all triangles
	* in the cloth grid, and calls the user-provided `func` with three Particle* ptrs corresponding to the triangle vertices.
	* @param func: any callable that takes (Particle*, Particle*, Particle*)
	*/
	template<typename F>
	void forEachTriangle(F&& func)
	{
		for (int x = 1; x < particles_width; x++)
		{
			for (int y = 1; y < particles_height; y++)
			{
				func(getParticle(x, y - 1), getParticle(x - 1, y - 1), getParticle(x - 1, y));
				func(getParticle(x, y), getParticle(x, y - 1), getParticle(x - 1, y));
			}
		}
	}


};