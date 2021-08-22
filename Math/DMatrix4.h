#pragma once

#include "DevMathHelpers.h"
#include "DVector3.h"
#include "DVector4.h"
#include "DQuaternion.h"

namespace DevEngine::Math {

//////////////////////////////////////////////////////////////////////////
////                     DevMath - 4x4 Matrix                         ////
//////////////////////////////////////////////////////////////////////////

	struct DMatrix4
	{
		/** Elements */
		union
		{
			float elements[4 * 4];
			DVector4 columns[4];
		};

		/** Constructors */
		DMatrix4();
		DMatrix4(const float* values);
		DMatrix4(float diagonal);
		DMatrix4(const DQuaternion& quaternion);


		/** Helper Functions */
		DMatrix4& multiply(const DMatrix4& other);


		/** Operator Overloads */
		friend DMatrix4 operator*(DMatrix4 current, const DMatrix4& other);

		DMatrix4& operator*=(const DMatrix4& other);

		void operator=(const DMatrix4& other);
		void operator=(const glm::mat4& other);
		//void operator=(const glm::mat4 other);


		/** Conversions to GLM */
		glm::mat4 ConvertToGLM();


		/** Static Functions */
		static DMatrix4 Identity();
		static DMatrix4 FromQuat(DQuaternion quaternion);

		static DMatrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static DMatrix4 Perspective(float fov, float aspectRatio, float near, float far);

		static DMatrix4 Translate(const DVector3& translation);
		static DMatrix4 Rotate(float angle, const DVector3& axis);
		static DMatrix4 Scale(const DVector3& scale);

		static DMatrix4 FromQuat(const DQuaternion& quaternion);
		static DMatrix4 Make(const float* values);
	};

}