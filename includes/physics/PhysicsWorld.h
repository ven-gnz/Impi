#pragma once

#include <physics/Spatial/BroadPhase.h>
#include <physics/Spatial/UniformGrid.h>
#include <physics/RigidBody_System/CollisionPrimitives.h>
#include <physics/RigidBody_System/CollisionDetector.h>
#include <physics/RigidBody_System/ContactResolver.h>
#include <physics/RigidBody_System/ForceRegistry.h>
#include <physics/Particle_System/ParticleWorld.h>
#include <physics/Objects/FireworkSystem.h>
#include <memory>


namespace Impi
{

class PhysicsWorld
{
public:


	PhysicsWorld();

	void update(real dt);
	void addBody(RigidBody*);
	void addCollider(CollisionPrimitive*);
	void registerForceGenerator(RigidBody*, ForceGenerator*);


	std::unique_ptr<BroadPhase> broadPhase;
	FireworkSystem& getFireworkSystem();

private:
	std::vector<RigidBody*> bodies;
	std::vector<CollisionPrimitive*> collisionPrimitives;

	unsigned maxContacts = 512;
	unsigned maxPotentialContacts = 1024;

	ForceRegistry registry;
	CollisionData cData;
	ContactResolver resolver;
	CollisionDetector detector;
	Contact contacts[512];
	PotentialContact potentialContacts[1024];

	CollisionPlane groundPlane;

	ParticleWorld particleWorld;
	FireworkSystem fireworkSystem;
	
};


}