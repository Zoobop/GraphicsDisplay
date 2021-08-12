#include "DVector2.h"

namespace ZM { namespace Math {

	//////////////////////////////////////////////////////////////////////////
	////                            2D Vector                             ////
	//////////////////////////////////////////////////////////////////////////

	DVector2::DVector2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	DVector2& DVector2::add(const DVector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	DVector2& DVector2::subtract(const DVector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	DVector2& DVector2::multiply(const DVector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	DVector2& DVector2::divide(const DVector2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	DVector2 operator+(DVector2 current, const DVector2& other)
	{
		return current.add(other);
	}

	DVector2 operator-(DVector2 current, const DVector2& other)
	{
		return current.subtract(other);
	}

	DVector2 operator*(DVector2 current, const DVector2& other)
	{
		return current.multiply(other);
	}

	DVector2 operator/(DVector2 current, const DVector2& other)
	{
		return current.divide(other);
	}

	DVector2& DVector2::operator+=(const DVector2& other)
	{
		return add(other);
	}

	DVector2& DVector2::operator-=(const DVector2& other)
	{
		return subtract(other);
	}

	DVector2& DVector2::operator*=(const DVector2& other)
	{
		return multiply(other);
	}

	DVector2& DVector2::operator/=(const DVector2& other)
	{
		return divide(other);
	}

	bool DVector2::operator==(const DVector2& other)
	{
		return x == other.x && y == other.y;
	}

	bool DVector2::operator!=(const DVector2& other)
	{
		return !(*this == other);
	}

	void DVector2::operator=(const DVector2& other)
	{
		x = other.x;
		y = other.y;
	}

	std::ostream& operator<<(std::ostream& stream, const DVector2& vector)
	{
		stream << "DVector2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

}}