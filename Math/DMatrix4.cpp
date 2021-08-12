#include "DMatrix4.h"

namespace ZM { namespace Math {

	//////////////////////////////////////////////////////////////////////////
	////                            4x4 Matrix                            ////
	//////////////////////////////////////////////////////////////////////////

	//////////////////----------- Constructors -----------////////////////////

	DMatrix4::DMatrix4()
	{
		for (auto i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
	}

	DMatrix4::DMatrix4(float diagonal)
	{
		for (auto i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	//////////////////--------- Helper Functions ---------////////////////////

	DMatrix4& DMatrix4::multiply(const DMatrix4& other)
	{
		/** Matrix multiplication (Column major) */
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}

				elements[x + y * 4] = sum;
			}
		}

		return *this;
	}

	//////////////////------- Operator Overloading --------////////////////////

	DMatrix4 operator*(DMatrix4 current, const DMatrix4& other)
	{
		return current.multiply(other);
	}

	DMatrix4& DMatrix4::operator*=(const DMatrix4& other)
	{
		return multiply(other);
	}

	//////////////////--------- Static Functions ---------////////////////////

	DMatrix4 DMatrix4::Identity()
	{
		return DMatrix4(1.0f);
	}

	DMatrix4 DMatrix4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		DMatrix4 result(1.0f);

		/** Diagonal */
		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		/** Last column */
		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	DMatrix4 DMatrix4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		DMatrix4 result(1.0f);

		/** Pre-calculation */
		float q = 1.0f / (float)tan(RAD2DEG(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}

	DMatrix4 DMatrix4::Translation(const DVector3& translation)
	{
		DMatrix4 result(1.0);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}

	DMatrix4 DMatrix4::Rotation(float angle, const DVector3& axis)
	{
		DMatrix4 result(1.0f);

		float r = (float)RAD2DEG(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		result.elements[0 + 0 * 4] = axis.x * omc + c;
		result.elements[1 + 0 * 4] = axis.y * axis.x * omc + axis.z * s;
		result.elements[2 + 0 * 4] = axis.x * axis.z * omc - axis.y * s;

		result.elements[0 + 1 * 4] = axis.x * axis.y * omc - axis.z * s;
		result.elements[1 + 1 * 4] = axis.y * omc + c;
		result.elements[2 + 1 * 4] = axis.y * axis.z * omc + axis.x * s;

		result.elements[0 + 2 * 4] = axis.x * axis.z * omc + axis.y * s;
		result.elements[1 + 2 * 4] = axis.y * axis.z * omc - axis.x * s;
		result.elements[2 + 2 * 4] = axis.z * omc + c;

		return result;
	}

	DMatrix4 DMatrix4::Scale(const DVector3& scale)
	{
		DMatrix4 result(1.0);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

}}