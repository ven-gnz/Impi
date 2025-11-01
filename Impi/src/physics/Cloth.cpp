#include "Cloth.h"

VerletCloth::VerletCloth(real width, real height, int num_particles_width, int num_particles_height)
	: particles_width(num_particles_width), particles_height(num_particles_height)
{
	particles.resize(num_particles_width * num_particles_height);


	// Particles : width and height are used to discretize the 
	for (int x = 0; x < num_particles_width; x++)
	{
		for (int y = 0; y < num_particles_height; y++)
		{
			Vector3 pos = Vector3(width * (x / (float)num_particles_width),
				-height * (y / (float)num_particles_height),
				0);
			particles[y * num_particles_width + x] = ClothParticle(pos);
		}
	}

	// Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
	// kept the original comment for clarity

	for (int x = 1; x < num_particles_width; x++)
	{
		for (int y = 1; y < num_particles_height; y++)
		{
			addToConstraints(getParticle(x - 1, y - 1), getParticle(x, y - 1));
			addToConstraints(getParticle(x - 1, y - 1), getParticle(x - 1, y));
			addToConstraints(getParticle(x - 1, y - 1), getParticle(x, y));
			addToConstraints(getParticle(x, y-1), getParticle(x-1, y));
		}
	}


	// secondary neighbors
	for (int x = 2; x < num_particles_width; x++)
	{
		for (int y = 2; y < num_particles_height; y++)
		{
			addToConstraints(getParticle(x-2, y-2), getParticle(x , y - 2));
			addToConstraints(getParticle(x-2, y-2), getParticle(x - 2, y));
			addToConstraints(getParticle(x - 2, y - 2), getParticle(x, y));
			addToConstraints(getParticle(x, y - 2), getParticle(x - 2 , y));
		}
	}

	// anchoring the topleft and bottom left corners
	for (int y = 0; y < 5; y++)
	{
		getParticle(0 + y, 0)->immobilise();
		getParticle(0, num_particles_height - y)->immobilise();
	}

}

Vector3 VerletCloth::getTriangleNormal(ClothParticle* p1, ClothParticle* p2, ClothParticle* p3)
{

	Vector3 pos1 = p1->getPosition();
	Vector3 pos2 = p2->getPosition();
	Vector3 pos3 = p3->getPosition();

	Vector3 v1 = pos2 - pos1;
	Vector3 v2 = pos3 - pos1;

	return v1.cross(v2);

}


void VerletCloth::addToConstraints(ClothParticle* p1, ClothParticle* p2)
{
	constraints.push_back(Constraint(p1, p2));
}

ClothParticle* VerletCloth::getParticle(int x, int y)
{
	return &particles[y * particles_width + x];
}