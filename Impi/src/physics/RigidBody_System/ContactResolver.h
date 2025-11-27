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

public:
	unsigned velocityIterationsUsed;
	unsigned positionIterationsUsed;

private:

	bool validSettings;
};



}