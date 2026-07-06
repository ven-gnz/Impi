#include <physics/PhysicsWorld.h>

using namespace Impi;


PhysicsWorld::PhysicsWorld() : resolver(64)
{
    cData.first_contact_in_array = contacts;
    cData.reset(MAX_CONTACTS);

    cData.friction = real(0.0);
    cData.restitution = real(0.001);
    cData.tolerance = real(0.001);

	groundPlane.direction = Vector3(0.001, 0.99, 0.001);
	groundPlane.offset = real(0);
}

void PhysicsWorld::update(real dt)
{
    registry.updateForces(dt);

    // 1. Plane box collisions
    for (size_t i = 0; i < collisionPrimitives.size(); ++i)
    {
        auto& primitive = collisionPrimitives[i];
        //std::cout << "Processing box " << i << " at position " << box.collider.body->getPosition() << "\n";
        if (!cData.hasMoreContacts()) return;
        if (auto* box = dynamic_cast<CollisionBox*>(primitive))
        {
            // check here in the future for if the cast is OK
            detector.boxAndHalfSpace(*box, groundPlane, &cData);
        }
        
        //std::cout << "After detector call, contactsLeft: " << cData.contactsLeft << "\n";

    }
    resolver.resolveContacts(contacts, cData.contactCount, dt);

    //generateContacts();

    cData.reset(MAX_CONTACTS);
    cData.friction = (real)0.0;
    cData.restitution = (real)0.001;
    cData.tolerance = (real)0.001;


    for (auto& primitive : collisionPrimitives)
    {
        primitive->calculateInternals();
    }

    // 2. Box Box collisions
    for (size_t i = 0; i < collisionPrimitives.size(); ++i)
    {

        for (size_t j = i + 1; j < collisionPrimitives.size(); ++j)
        {
            auto* a = dynamic_cast<CollisionBox*>(collisionPrimitives[i]);
            auto* b = dynamic_cast<CollisionBox*>(collisionPrimitives[j]);

            if (a && b)
            {
                detector.boxAndBox(*a, *b, &cData);
            }

            if (!cData.hasMoreContacts()) return;
            detector.boxAndBox(*a,*b, &cData);
        }
    }
    for (auto* body : bodies)
    {
        body->integrate(dt);
        //body->calculateInternals();
    }


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