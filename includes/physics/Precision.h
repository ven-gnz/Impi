#pragma once

#include <cmath>
#include <float.h>

/*
	Impi is a 32float system, another typedef can be done
*/
namespace Impi {

	typedef float real;
#define real_sqrt sqrtf
#define real_pow powf
#define real_abs fabsf

#define real_sin sinf
#define real_cos cosf
#define real_exp expf
#define real_epsilon FLT_EPSILON
}
