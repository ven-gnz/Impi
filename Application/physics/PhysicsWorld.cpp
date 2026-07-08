#include <physics/PhysicsWorld.h>

using namespace Impi;


PhysicsWorld::PhysicsWorld() :
    resolver(32),
    particleWorld(1, 1024),
    fireworkSystem()
{

    contacts.resize(maxContacts);
    potentialContacts.resize(maxPotentialContacts);

    fireworkSystem.init(4096);
    cData.first_contact_in_array = contacts.data();
    cData.reset(maxContacts);
    

    cData.friction = real(0.0);
    cData.restitution = real(0.001);
    cData.tolerance = real(0.001);

	groundPlane.direction = Vector3(0.001, 0.99, 0.001);
	groundPlane.offset = real(0);
    broadPhase = std::make_unique<UniformGrid>();

}

void PhysicsWorld::update(real dt)
{

    registry.updateForces(dt);
    for (RigidBody* body : bodies)
    {
        body->integrate(dt);
    }

    for (CollisionPrimitive* primitive : collisionPrimitives)
    {
        primitive->calculateInternals();
    }

    cData.reset(maxContacts);
    cData.friction = (real)0.0;
    cData.restitution = (real)0.001;
    cData.tolerance = (real)0.001;


    broadPhase->clear();

    for (CollisionPrimitive* primitive : collisionPrimitives)
    {
        broadPhase->insert(primitive);
    }

    for (CollisionPrimitive* primitive : collisionPrimitives)
    {
        if (!cData.hasMoreContacts())
            break;

        if (auto* box = dynamic_cast<CollisionBox*>(primitive))
        {
            detector.boxAndHalfSpace(*box, groundPlane, &cData);
        }
    }

    unsigned pairCount =
        broadPhase->generatePairs(
            potentialContacts.data(),
            maxPotentialContacts);


    for (unsigned i = 0; i < pairCount; ++i)
    {
        if (!cData.hasMoreContacts())
            break;

        CollisionPrimitive* first = potentialContacts[i].first;
        CollisionPrimitive* second = potentialContacts[i].second;

        auto* boxA = dynamic_cast<CollisionBox*>(first);
        auto* boxB = dynamic_cast<CollisionBox*>(second);

        if (boxA && boxB)
        {
            detector.boxAndBox(*boxA, *boxB, &cData);
        }
    }

    std::cout
        << "Pairs: " << pairCount
        << " Contacts: " << cData.contactCount
        << '\n';


    resolver.resolveContacts(
        contacts.data(),
        cData.contactCount,
        dt);

    fireworkSystem.update(dt);

}

FireworkSystem& PhysicsWorld::getFireworkSystem()
{
    return fireworkSystem;
  
}


void PhysicsWorld::addBody(RigidBody* b)
{
    bodies.push_back(b);
}
void PhysicsWorld::addCollider(CollisionPrimitive* p)
{
    collisionPrimitives.push_back(p);
}
void PhysicsWorld::registerForceGenerator(RigidBody* r, ForceGenerator* fg)
{
    registry.add(r, fg);
}