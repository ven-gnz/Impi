#pragma once
#include "Contact.h"

namespace Impi
{



	class ContactResolver
	{
		
		
	protected:

		unsigned velocityIterations;

		unsigned positionIterations;

		real velocityEpsilon;
		real positionEpsilon;

		void prepareContacts(Contact *contactArray, unsigned numContacts, real duration);

		void setIterations(unsigned velocityIterations, unsigned positionIterations);

		void setEpsilon(real velocityEpsilon, real positionEpsilon);

		void setIterations(unsigned iterations);

	public:
		unsigned velocityIterationsUsed;
		unsigned positionIterationsUsed;

		void adjustVelocities(Contact *c,
			unsigned numContacts,
			real duration);

		void adjustPositions(Contact *c,
			unsigned numContacts,
			real duration);


		void resolveContacts(Contact* contactArray, unsigned numContacts, real duration);



	private:

		bool validSettings;

	public:

		ContactResolver(unsigned iterations,
			real velocityEpsilon = (real)0.001,
			real positionEpsilon = (real)0.001);

		

	};



}