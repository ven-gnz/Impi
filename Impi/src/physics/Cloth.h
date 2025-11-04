#pragma once
#include <vector>
#include <Particle.h>
#include <ParticleLinks.h>
#include <Constraint.h>

class VerletCloth
{

	int particles_width;
	int particles_height;
	real width;
	real height;

	const int constraint_iterations = 15;

	std::vector<ClothParticle> particles;
	std::vector<Constraint> constraints;

	std::vector<Vector3> initialPositions;

	Vector3 TopLeftCornerPos;
	

public:
	VerletCloth(real width, real height, int num_particles_width, int num_particles_height, Vector3 TopLeftCornerPos);


	/**
	* Get the particle by its relative position in grid for update and constructor
	*/
	ClothParticle* getParticle(int x, int y);


	/**
	* Const get particle pointer for template use
	*/
	const ClothParticle* getParticle(int x, int y) const;

	/**
	* Get the particle index on the flat particles array for EBO setup
	*/
	int getParticleIndex(const ClothParticle* p) const;

	void addToConstraints(ClothParticle* p1, ClothParticle* p2);

	Vector3 getTriangleNormal(const ClothParticle* p1, const ClothParticle* p2, const ClothParticle* p3) const;

	void updateClothParticles(real dt);

	const std::vector<ClothParticle> getParticles() const;

	void returnToStartingPositions();

	/**
	* Adds a per triangle force for the cloth
	*/
	void addDottedForce(const Vector3& forceDirection);

	/**
	* Adds a force acting on all particles separately
	*/
	void addForceToCloth(Vector3 force);

	const int getWidthCount() const;
	const int getHeightCount() const;

	const real minX();
	const real maxX();

	std::vector<Vector3> getVertices() const;
	std::vector<Vector3> getNormals() const; 

	// My first template (:

	/**
	 * Convenience function that iterates over all triangles
	* in the cloth grid, and calls the user-provided `func` with three Particle* ptrs corresponding to the triangle vertices.
	* @param func: any callable that takes (Particle*, Particle*, Particle*)
	*/
	template<typename F>
	void forEachTriangle(F&& func) const
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

	template<typename F>
	void mutateEachTriangle(F&& func)
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