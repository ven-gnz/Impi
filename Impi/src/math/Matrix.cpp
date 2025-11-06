#include "Matrix.h"
#include "Quaternion.h"

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


Matrix3 Matrix3::operator*(const Matrix3& o)
{
	
		return Matrix3
		(data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
			data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
			data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],
			data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
			data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
			data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],
			data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
			data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
			data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
		);
	
}

Matrix3 Matrix3::inverse() const
{
    Matrix3 result;
    result.setInverse(*this);
    return result;
}

void Matrix3::invert() { setInverse(*this); }



void Matrix3::setInverse(const Matrix3& m)
{

	real t4 = m.data[0] * m.data[4];
	real t6 = m.data[0] * m.data[5];
	real t8 = m.data[1] * m.data[3];
	real t10 = m.data[2] * m.data[3];
	real t12 = m.data[1] * m.data[6];
	real t14 = m.data[2] * m.data[6];

	real det = (t4 * m.data[8] 
		- t6 * m.data[7] 
		- t8 * m.data[8] 
		+ t10 * m.data[7] 
		+ t12 * m.data[5] 
		- t14 * m.data[4]);

	if (det == (real)0.0f) return;

	real t17 = 1 / det;

	data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7]) * t17;
	data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7]) * t17;
	data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4]) * t17;
	data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6]) * t17;
	data[4] = (m.data[0] * m.data[8] - t14) * t17;
	data[5] = -(t6 - t10) * t17;
	data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6]) * t17;
	data[7] = -(m.data[0] * m.data[7] - t12) * t17;
	data[8] = (t4 - t8) * t17;
}


void Matrix3::setTranspose(const Matrix3& m)
{
	data[0] = m.data[0];
	data[1] = m.data[3];
	data[2] = m.data[6];
	data[3] = m.data[1];
	data[4] = m.data[4];
	data[5] = m.data[7];
	data[6] = m.data[2];
	data[7] = m.data[5];
	data[8] = m.data[8];
}

Matrix3 Matrix3::transpose() const
{
	Matrix3 result;
	result.setTranspose(*this);
	return result;
}













Matrix4::Matrix4()
{
	data[1] = data[2] = data[3] = data[4] = data[6] =
		data[7] = data[8] = data[9] = data[11] = 0;
	data[0] = data[5] = data[10] = 1;
}

Vector3 Matrix4::transform(const Vector3& vector) const
{
	return (*this) * vector;
}


Vector3 Matrix4::operator*(const Vector3& vector) const
{
	return Vector3(
		vector.x * data[0] +
		vector.y * data[1] +
		vector.z * data[2],
		vector.x * data[4] +
		vector.y * data[5] +
		vector.z * data[6],
		vector.x * data[8] +
		vector.y * data[9] +
		vector.y * data[10]);
}

Matrix4 Matrix4::operator*(const Matrix4& o) const
{

	Matrix4 result;
	result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) + (o.data[8] * data[2]);
	result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) + (o.data[8] * data[6]);
	result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) + (o.data[8] * data[10]);

	result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) + (o.data[9] * data[2]);
	result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) + (o.data[9] * data[6]);
	result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) + (o.data[9] * data[10]);

	result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) + (o.data[10] * data[2]);
	result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) + (o.data[10] * data[6]);
	result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) + (o.data[10] * data[10]);

	result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) + (o.data[11] * data[2]) + data[3];
	result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) + (o.data[11] * data[6]) + data[7];
	result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) + (o.data[11] * data[10]) + data[11];

	return result;
}


/** Returns a new matrix containing the inverse of this matrix. */
Matrix4 Matrix4::inverse() const
{
	Matrix4 result;
	result.setInverse(*this);
	return result;
}

/**
 * Inverts the matrix.
 */
void Matrix4::invert()
{
	setInverse(*this);
}

real Matrix4::getDeterminant() const
{
	return -data[8] * data[5] * data[2] +
		data[4] * data[9] * data[2] +
		data[8] * data[1] * data[6] -
		data[0] * data[9] * data[6] -
		data[4] * data[1] * data[10] +
		data[0] * data[5] * data[10];
}

void Matrix4::setInverse(const Matrix4& m)
{
	
	real det = getDeterminant();
	if (det == 0) return;
	det = ((real)1.0) / det;

	data[0] = (-m.data[9] * m.data[6] + m.data[5] * m.data[10]) * det;
	data[4] = (m.data[8] * m.data[6] - m.data[4] * m.data[10]) * det;
	data[8] = (-m.data[8] * m.data[5] + m.data[4] * m.data[9]) * det;

	data[1] = (m.data[9] * m.data[2] - m.data[1] * m.data[10]) * det;
	data[5] = (-m.data[8] * m.data[2] + m.data[0] * m.data[10]) * det;
	data[9] = (m.data[8] * m.data[1] - m.data[0] * m.data[9]) * det;

	data[2] = (-m.data[5] * m.data[2] + m.data[1] * m.data[6]) * det;
	data[6] = (+m.data[4] * m.data[2] - m.data[0] * m.data[6]) * det;
	data[10] = (-m.data[4] * m.data[1] + m.data[0] * m.data[5]) * det;

	data[3] = (m.data[9] * m.data[6] * m.data[3]
		- m.data[5] * m.data[10] * m.data[3]
		- m.data[9] * m.data[2] * m.data[7]
		+ m.data[1] * m.data[10] * m.data[7]
		+ m.data[5] * m.data[2] * m.data[11]
		- m.data[1] * m.data[6] * m.data[11]) * det;
	data[7] = (-m.data[8] * m.data[6] * m.data[3]
		+ m.data[4] * m.data[10] * m.data[3]
		+ m.data[8] * m.data[2] * m.data[7]
		- m.data[0] * m.data[10] * m.data[7]
		- m.data[4] * m.data[2] * m.data[11]
		+ m.data[0] * m.data[6] * m.data[11]) * det;
	data[11] = (m.data[8] * m.data[5] * m.data[3]
		- m.data[4] * m.data[9] * m.data[3]
		- m.data[8] * m.data[1] * m.data[7]
		+ m.data[0] * m.data[9] * m.data[7]
		+ m.data[4] * m.data[1] * m.data[11]
		- m.data[0] * m.data[5] * m.data[11]) * det;
}

std::array<float,16> Matrix4::getGLarray()
{
	std::array<float, 16> renderArray;
	fillGLArray(renderArray.data());
	return renderArray;
}

void Matrix4::fillGLArray(float array[16]) const
{
	{
		array[0] = (float)data[0];
		array[1] = (float)data[4];
		array[2] = (float)data[8];
		array[3] = (float)0;

		array[4] = (float)data[1];
		array[5] = (float)data[5];
		array[6] = (float)data[9];
		array[7] = (float)0;

		array[8] = (float)data[2];
		array[9] = (float)data[6];
		array[10] = (float)data[10];
		array[11] = (float)0;

		array[12] = (float)data[3];
		array[13] = (float)data[7];
		array[14] = (float)data[11];
		array[15] = (float)1;
	}
}