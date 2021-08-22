#include "DVector3.h"

namespace DevEngine::Math {

	//////////////////////////////////////////////////////////////////////////
	////                            3D Vector                             ////
	//////////////////////////////////////////////////////////////////////////

	DVector3::DVector3(const glm::vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	DVector3::DVector3(const float* values)
	{
		x = values[0];
		y = values[1];
		z = values[2];
	}

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

	DVector3& DVector3::add(const glm::vec3& other)
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

	DVector3& DVector3::multiply(const float& other)
	{
		x *= other;
		y *= other;
		z *= other;
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

	DVector3 operator*(DVector3 current, const float& other)
	{
		return DVector3();
	}

	DVector3 operator*(float current, const DVector3& other)
	{
		return DVector3();
	}

	DVector3 operator/(DVector3 current, const DVector3& other)
	{
		return current.divide(other);
	}

	DVector3 operator-(const DVector3& current)
	{
		return DVector3();
	}

	DVector3& DVector3::operator+=(const DVector3& other)
	{
		return add(other);
	}

	DVector3& DVector3::operator+=(const glm::vec3& other)
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

	DVector3& DVector3::operator*=(const float& other)
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

	bool DVector3::operator<=(const DVector3& other)
	{
		return false;
	}

	bool DVector3::operator>=(const DVector3& other)
	{
		return false;
	}

	bool DVector3::operator<=(const float& other)
	{
		return false;
	}

	bool DVector3::operator>=(const float& other)
	{
		return false;
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

	void DVector3::operator=(const glm::vec3& other)
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

	glm::vec3 DVector3::ConvertToGLM() const
	{
		return glm::vec3(x, y, z);
	}

	float DVector3::Length() const
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	DVector3 DVector3::Normalize()
	{
		return DVector3();
	}

	DVector3 DVector3::Make(const float* values)
	{
		return DVector3(values);
	}

	DVector3 DVector3::Zero()
	{
		return DVector3(0.0f, 0.0f, 0.0f);
	}

	DVector3 DVector3::Identity()
	{
		return DVector3(1.0f, 1.0f, 1.0f);
	}

}