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

	static constexpr unsigned DefaultContactCapacity = 16384;
	static constexpr unsigned DefaultPotentialCapacity = 65536;

private:
	std::vector<RigidBody*> bodies;
	std::vector<CollisionPrimitive*> collisionPrimitives;

	unsigned maxContacts = DefaultContactCapacity;
		unsigned maxPotentialContacts = DefaultPotentialCapacity;

	ForceRegistry registry;
	CollisionData cData;
	ContactResolver resolver;
	CollisionDetector detector;
	std::vector<Contact> contacts;
	std::vector<PotentialContact> potentialContacts;

	CollisionPlane groundPlane;

	ParticleWorld particleWorld;
	FireworkSystem fireworkSystem;
	
};


}