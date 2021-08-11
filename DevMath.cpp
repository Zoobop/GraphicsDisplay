#include "DevMath.h"

//////////////////////////////////////////////////////////////////////////
////                            2D Vector                             ////
//////////////////////////////////////////////////////////////////////////


ZM::Math::DVector2::DVector2()
{
	x = 0.0f;
	y = 0.0f;
}


ZM::Math::DVector2::DVector2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

ZM::Math::DVector2& ZM::Math::DVector2::add(const DVector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

ZM::Math::DVector2& ZM::Math::DVector2::subtract(const DVector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

ZM::Math::DVector2& ZM::Math::DVector2::multiply(const DVector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

ZM::Math::DVector2& ZM::Math::DVector2::divide(const DVector2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

ZM::Math::DVector2& operator+(ZM::Math::DVector2& current, const ZM::Math::DVector2& other)
{
	return current.add(other);
}

ZM::Math::DVector2& operator-(ZM::Math::DVector2& current, const ZM::Math::DVector2& other)
{
	return current.subtract(other);
}

ZM::Math::DVector2& operator*(ZM::Math::DVector2& current, const ZM::Math::DVector2& other)
{
	return current.multiply(other);
}

ZM::Math::DVector2& operator/(ZM::Math::DVector2& current, const ZM::Math::DVector2& other)
{
	return current.divide(other);
}

ZM::Math::DVector2& ZM::Math::DVector2::operator+=(const DVector2& other)
{
	return add(other);
}

ZM::Math::DVector2& ZM::Math::DVector2::operator-=(const DVector2& other)
{
	return subtract(other);
}

ZM::Math::DVector2& ZM::Math::DVector2::operator*=(const DVector2& other)
{
	return multiply(other);
}

ZM::Math::DVector2& ZM::Math::DVector2::operator/=(const DVector2& other)
{
	return divide(other);
}

bool ZM::Math::DVector2::operator==(const DVector2& other)
{
	return x == other.x && y == other.y;
}

bool ZM::Math::DVector2::operator!=(const DVector2& other)
{
	return !(*this == other);
}

void ZM::Math::DVector2::operator=(const DVector2& other)
{
	x = other.x;
	y = other.y;
}

std::ostream& ZM::Math::DVector2::operator<<(std::ostream& stream)
{
	stream << "DVector2: (" << x << ", " << y << ")";
	return stream;
}


//////////////////////////////////////////////////////////////////////////
////                            3D Vector                             ////
//////////////////////////////////////////////////////////////////////////


ZM::Math::DVector3::DVector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

ZM::Math::DVector3::DVector3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


//////////////////////////////////////////////////////////////////////////
////                            4D Vector                             ////
//////////////////////////////////////////////////////////////////////////