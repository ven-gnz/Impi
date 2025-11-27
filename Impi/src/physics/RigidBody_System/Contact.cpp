#include "Contact.h"

using namespace Impi;

void Contact::calculateContactBasis()
{

	Vector3 contactTangent[2];

	
	if (real_abs(contactNormal.x) > real_abs(contactNormal.y))
	{
		const real s = (real)1.0f /
			real_sqrt(
				contactNormal.z * contactNormal.z +
				contactNormal.x * contactNormal.x);

		// The new X-axis is at right angles to the world Y-axis
		contactTangent[0].x = contactNormal.z * s;
		contactTangent[0].y = 0;
		contactTangent[0].z = -contactNormal.x * s;

		contactTangent[1].x = contactNormal.y * contactTangent[0].x;
		contactTangent[1].y = contactNormal.z*contactTangent[0].x 
			- contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
	}
	else
	{
		const real s = (real)1.0f /
			real_sqrt(
				contactNormal.z * contactNormal.z +
				contactNormal.x * contactNormal.x);

		// The new X-axis is at right angles to the world X-axis
		contactTangent[0].x = 0;
		contactTangent[0].y = -contactNormal.z * s;
		contactTangent[0].z = contactNormal.y * s;

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].x = contactNormal.y * contactTangent[0].z -
			contactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = contactNormal.x * contactTangent[0].y;

	}

	contactToWorldSpace.setComponents(
		contactNormal,
		contactTangent[0],
		contactTangent[1]
	);
}