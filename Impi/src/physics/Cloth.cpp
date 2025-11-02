#include "Cloth.h"

VerletCloth::VerletCloth(real width, real height, int num_particles_width, int num_particles_height,Vector3 TopLeftCornerPos)
	: width(width),height(height), particles_width(num_particles_width), particles_height(num_particles_height), TopLeftCornerPos(TopLeftCornerPos)
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
			pos += TopLeftCornerPos;
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

Vector3 VerletCloth::getTriangleNormal(const ClothParticle* p1, const ClothParticle* p2, const ClothParticle* p3)
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

const ClothParticle* VerletCloth::getParticle(int x, int y) const
{
	return &particles[y * particles_width + x];
}

void VerletCloth::updateClothParticles(real dt)
{

	std::vector<Constraint>::iterator constraint;

	for (int i = 0; i < constraint_iterations; i++)
	{
		for (constraint = constraints.begin(); constraint != constraints.end(); constraint++)
		{
			(*constraint).SatisfyConstraint(); 
		}
	}

	std::vector<ClothParticle>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).integrate(dt); // calculate the position of each particle at the next time step.
	}

}

void VerletCloth::addDottedForce(const Vector3& forceDirection)
{
	mutateEachTriangle([&](ClothParticle* p1, ClothParticle* p2, ClothParticle* p3)
		{
			Vector3 normal = getTriangleNormal(p1, p2, p3);

			Vector3 force = normal * (normal.normalized().dot(forceDirection));
			p1->addForce(force);
			p2->addForce(force);
			p3->addForce(force);
		});
}

void VerletCloth::addForceToCloth(Vector3 force)
{
	for (auto &p : particles)
	{
		p.addForce(force);
	}
}

std::vector<Vector3> VerletCloth::getVertices() const
{
	std::vector<Vector3> verts;
	verts.reserve(particles.size());
	for (const auto& p : particles)
		verts.push_back(p.getPosition());
	return verts;
}


int VerletCloth::getParticleIndex(const ClothParticle* p) const
{
	return static_cast<int>(p - &particles[0]);
}

std::vector<Vector3> VerletCloth::getNormals() const
{
	std::vector<Vector3> normals(particles.size(), Vector3(0,0,0));

	forEachTriangle([&](const ClothParticle* p1, const ClothParticle* p2, const ClothParticle* p3)
		{
			Vector3 n = getTriangleNormal(const p1, const p2, const p3);

			int i1 = getParticleIndex(p1);
			int i2 = getParticleIndex(p2);
			int i3 = getParticleIndex(p3);

			normals[i1] += n;
			normals[i2] += n;
			normals[i3] += n;
		});

	for (auto& n : normals)
		n.normalize();

	return normals;
}

const real VerletCloth::minX()
{
	return TopLeftCornerPos.x;
}

const real VerletCloth::maxX()
{
	return TopLeftCornerPos.x + width;
}

const int VerletCloth::getWidthCount() const{ return particles_width;  }
const int VerletCloth::getHeightCount() const{ return particles_height; }

const std::vector<ClothParticle> VerletCloth::getParticles() const
{
	return particles;
}

