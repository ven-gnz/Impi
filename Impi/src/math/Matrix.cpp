#include "Matrix.h"

using namespace Impi;


Matrix3::Matrix3
(real c0, real c1, real c2,
 real c3, real c4, real c5,
 real c6, real c7, real c8
)
{
    data[0] = c0; data[1] = c1; data[2] = c2;
    data[3] = c3; data[4] = c4; data[5] = c5;
    data[6] = c6; data[7] = c7; data[8] = c8;
}

Matrix3::Matrix3()
{
    data[0] = data[1] = data[2] = 0;
    data[3] = data[4] = data[5] = 0;
    data[6] = data[7] = data[8] = 0;
}

