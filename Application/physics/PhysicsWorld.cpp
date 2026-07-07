#include <physics/PhysicsWorld.h>

using namespace Impi;


PhysicsWorld::PhysicsWorld() :
    resolver(64),
    maxContacts(256),
    maxPotentialContacts(1024)
{
    cData.first_contact_in_array = contacts;
    cData.reset(256);

    cData.friction = real(0.0);
    cData.restitution = real(0.001);
    cData.tolerance = real(0.001);

	groundPlane.direction = Vector3(0.001, 0.99, 0.001);
	groundPlane.offset = real(0);
    broadPhase = std::make_unique<UniformGrid>();

}

void PhysicsWorld::update(real dt)
{
    // YE NEWYE
    registry.updateForces(dt);
    for (RigidBody* body : bodies)
    {
        body->integrate(dt);
    }

    for (CollisionPrimitive* primitive : collisionPrimitives)
    {
        primitive->calculateInternals();
    }

    cData.reset(256);
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
            potentialContacts,
            1024);


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


    resolver.resolveContacts(
        contacts,
        cData.contactCount,
        dt);

  
    ///* YE OLDE*/
    //// 1. Plane box collisions
    //for (size_t i = 0; i < collisionPrimitives.size(); ++i)
    //{
    //    auto& primitive = collisionPrimitives[i];
    //    if (!cData.hasMoreContacts()) return;
    //    if (auto* box = dynamic_cast<CollisionBox*>(primitive))
    //    {
    //        // check here in the future for if the cast is OK
    //        detector.boxAndHalfSpace(*box, groundPlane, &cData);
    //    }

    //}
    //resolver.resolveContacts(contacts, cData.contactCount, dt);

    //


    //for (auto& primitive : collisionPrimitives)
    //{
    //    primitive->calculateInternals();
    //}

    //// 2. Box Box collisions
    //for (size_t i = 0; i < collisionPrimitives.size(); ++i)
    //{

    //    for (size_t j = i + 1; j < collisionPrimitives.size(); ++j)
    //    {
    //        auto* a = dynamic_cast<CollisionBox*>(collisionPrimitives[i]);
    //        auto* b = dynamic_cast<CollisionBox*>(collisionPrimitives[j]);

    //        if (a && b)
    //        {
    //            detector.boxAndBox(*a, *b, &cData);
    //        }

    //        if (!cData.hasMoreContacts()) return;
    //        detector.boxAndBox(*a,*b, &cData);
    //    }
    //}
    //for (auto* body : bodies)
    //{
    //    body->integrate(dt);
    //    //body->calculateInternals();
    //}


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