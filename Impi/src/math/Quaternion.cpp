#include "Quaternion.h"

using namespace Impi;

Quaternion::Quaternion() : r(1), i(0), j(0), k(0) { }


Quaternion::Quaternion(const real r, const real i, const real j, const real k)
    : r(r), i(i), j(j), k(k)
{}


void Quaternion::normalise()
{
    real d = r * r + i * i + j * j + k * k;

    // Check for zero length quaternion, and use the no-rotation
    // quaternion in that case.
    if (d < real_epsilon) {
        r = 1;
        return;
    }

    d = ((real)1.0) / real_sqrt(d);
    r *= d;
    i *= d;
    j *= d;
    k *= d;
}

void Quaternion::operator *=(const Quaternion& multiplier)
{
    Quaternion q = *this;
    r = q.r * multiplier.r - q.i * multiplier.i -
        q.j * multiplier.j - q.k * multiplier.k;
    i = q.r * multiplier.i + q.i * multiplier.r +
        q.j * multiplier.k - q.k * multiplier.j;
    j = q.r * multiplier.j + q.j * multiplier.r +
        q.k * multiplier.i - q.i * multiplier.k;
    k = q.r * multiplier.k + q.k * multiplier.r +
        q.i * multiplier.j - q.j * multiplier.i;
}

void Quaternion::rotateByVector(const Vector3& vector)
{
    Quaternion q(0, vector.x, vector.y, vector.z);
    (*this) *= q;
}

void Quaternion::addScaledVector(const Vector3& vector, real scale)
{
    Quaternion q(0,
        vector.x * scale,
        vector.y * scale,
        vector.z * scale);
    q *= *this;
    r += q.r * ((real)0.5);
    i += q.i * ((real)0.5);
    j += q.j * ((real)0.5);
    k += q.k * ((real)0.5);
}

Vector3 Quaternion::rotateInverse(const Vector3& v) const
{
   
    float w = r;
    float x = -i; // q^-1
    float y = -j;
    float z = -k;

    // Quaternion multiplication: q^-1 * v * q
    // Step 1: q^-1 * v
    float w1 = -x * v.x - y * v.y - z * v.z;
    float x1 = w * v.x + y * v.z - z * v.y;
    float y1 = w * v.y + z * v.x - x * v.z;
    float z1 = w * v.z + x * v.y - y * v.x;

    // Step 2: result * q
    float rw = w1 * w - x1 * i - y1 * j - z1 * k;
    float rx = w1 * i + x1 * w + y1 * k - z1 * j;
    float ry = w1 * j - x1 * k + y1 * w + z1 * i;
    float rz = w1 * k + x1 * j - y1 * i + z1 * w;

    return Vector3(rx, ry, rz);
}