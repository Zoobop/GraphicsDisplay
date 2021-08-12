#include "DVector4.h"

namespace ZM { namespace Math {

	//////////////////////////////////////////////////////////////////////////
	////                            4D Vector                             ////
	//////////////////////////////////////////////////////////////////////////

	DVector4::DVector4(const float& x, const float& y, const float& z, const float& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	DVector4& ZM::Math::DVector4::add(const DVector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	DVector4& DVector4::subtract(const DVector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	DVector4& DVector4::multiply(const DVector4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	DVector4& DVector4::divide(const DVector4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	DVector4 operator+(DVector4 current, const DVector4& other)
	{
		return current.add(other);
	}

	DVector4 operator-(DVector4 current, const DVector4& other)
	{
		return current.subtract(other);
	}

	DVector4 operator*(DVector4 current, const DVector4& other)
	{
		return current.multiply(other);
	}

	DVector4 operator/(DVector4 current, const DVector4& other)
	{
		return current.divide(other);
	}

	DVector4& DVector4::operator+=(const DVector4& other)
	{
		return add(other);
	}

	DVector4& DVector4::operator-=(const DVector4& other)
	{
		return subtract(other);
	}

	DVector4& DVector4::operator*=(const DVector4& other)
	{
		return multiply(other);
	}

	DVector4& DVector4::operator/=(const DVector4& other)
	{
		return divide(other);
	}

	bool DVector4::operator==(const DVector4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool DVector4::operator!=(const DVector4& other)
	{
		return !(*this == other);
	}

	void DVector4::operator=(const DVector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	std::ostream& operator<<(std::ostream& stream, const DVector4& vector)
	{
		stream << "DVector4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return stream;
	}
}}