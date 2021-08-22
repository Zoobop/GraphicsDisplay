#include "DQuaternion.h"
#include <glm/ext/quaternion_float.hpp>

namespace DevEngine::Math {


	DQuaternion::DQuaternion(const float& x, const float& y, const float& z, const float& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	DQuaternion::DQuaternion(const float* values)
	{
		x = values[0];
		y = values[1];
		z = values[2];
		w = values[3];
	}

	//////////////////--------- Helper Functions ---------////////////////////

	DQuaternion& DQuaternion::multiply(const DQuaternion& other)
	{
		float w_ = w * other.w - x * other.x - y * other.y - z * other.z;
		float x_ = x * other.w + w * other.x + y * other.z - z * other.y;
		float y_ = z * other.w + w * other.y + z * other.x - x * other.z;
		float z_ = y * other.w + w * other.z + x * other.y - y * other.x;

		this->x = x_;
		this->y = y_;
		this->z = z_;
		this->w = w_;

		return *this;
	}

	DQuaternion& DQuaternion::multiply(const DVector3& other)
	{
		float w_ = -x * other.x - y * other.y - z * other.z;
		float x_ = w * other.x + y * other.z - z * other.y;
		float y_ = w * other.y + z * other.x - x * other.z;
		float z_ = w * other.z + x * other.y - y * other.x;

		this->x = x_;
		this->y = y_;
		this->z = z_;
		this->w = w_;

		return *this;
	}

	//////////////////------- Operator Overloading --------////////////////////

	DQuaternion operator*(DQuaternion current, const DQuaternion& other)
	{
		return current.multiply(other);
	}

	DQuaternion operator*(DQuaternion current, const DVector3& other)
	{
		return current.multiply(other);
	}

	DQuaternion& DQuaternion::operator*=(const DQuaternion& other)
	{
		return multiply(other);
	}

	DQuaternion& DQuaternion::operator*=(const DVector3& other)
	{
		return multiply(other);
	}

	void DQuaternion::operator=(const DQuaternion& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	void DQuaternion::operator=(const glm::quat& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}



	glm::quat DQuaternion::ConvertToGLM() const
	{
		return glm::quat(x, y, z, w);
	}

	float DQuaternion::Length() const
	{
		return (float)sqrt(x * x + y * y + z * z + w * w);
	}

	DQuaternion DQuaternion::Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;
		w /= length;

		return *this;
	}

	DQuaternion DQuaternion::Conjugate()
	{
		return DQuaternion(-x, -y, -z, -w);
	}

	DQuaternion DQuaternion::Make(const float* values)
	{
		return DQuaternion(values[0], values[1], values[2], values[3]);
	}

	DQuaternion DQuaternion::Zero()
	{
		return DQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
	}

	DQuaternion DQuaternion::Identity()
	{
		return DQuaternion(1.0f, 1.0f, 1.0f, 1.0f);
	}

}