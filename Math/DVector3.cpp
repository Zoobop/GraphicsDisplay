#include "DVector3.h"

namespace ZM { namespace Math {

	//////////////////////////////////////////////////////////////////////////
	////                            3D Vector                             ////
	//////////////////////////////////////////////////////////////////////////

	DVector3::DVector3(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	DVector3& DVector3::add(const DVector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	DVector3& DVector3::subtract(const DVector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	DVector3& DVector3::multiply(const DVector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	DVector3& DVector3::divide(const DVector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	DVector3 operator+(DVector3 current, const DVector3& other)
	{
		return current.add(other);
	}

	DVector3 operator-(DVector3 current, const DVector3& other)
	{
		return current.subtract(other);
	}

	DVector3 operator*(DVector3 current, const DVector3& other)
	{
		return current.multiply(other);
	}

	DVector3 operator/(DVector3 current, const DVector3& other)
	{
		return current.divide(other);
	}

	DVector3& DVector3::operator+=(const DVector3& other)
	{
		return add(other);
	}

	DVector3& DVector3::operator-=(const DVector3& other)
	{
		return subtract(other);
	}

	DVector3& DVector3::operator*=(const DVector3& other)
	{
		return multiply(other);
	}

	DVector3& DVector3::operator/=(const DVector3& other)
	{
		return divide(other);
	}

	bool DVector3::operator==(const DVector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool DVector3::operator!=(const DVector3& other)
	{
		return !(*this == other);
	}

	void DVector3::operator=(const DVector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	std::ostream& operator<<(std::ostream& stream, const DVector3& vector)
	{
		stream << "DVector3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

}}