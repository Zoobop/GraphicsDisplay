#pragma once

#include "DevMathHelpers.h"
#include "DVector3.h"

namespace DevEngine::Math {

	struct DQuaternion
	{
		float x, y, z, w;

		/** Constructors */
		DQuaternion(const float* values);
		DQuaternion(const float& x, const float& y, const float& z, const float& w);

		/** Helper Functions */
		DQuaternion& multiply(const DQuaternion& other);
		DQuaternion& multiply(const DVector3& other);

		/** Operator Overloading */
		friend DQuaternion operator*(DQuaternion current, const DQuaternion& other);
		friend DQuaternion operator*(DQuaternion current, const DVector3& other);

		DQuaternion& operator*=(const DQuaternion& other);
		DQuaternion& operator*=(const DVector3& other);

		void operator=(const DQuaternion& other);
		void operator=(const glm::quat& other);

		/** Convert To GLM */
		glm::quat ConvertToGLM() const;

		float Length() const;

		DQuaternion Normalize();
		DQuaternion Conjugate();

		/** Static Functions */
		static DQuaternion Make(const float* values);
		static DQuaternion Zero();
		static DQuaternion Identity();
	};

}