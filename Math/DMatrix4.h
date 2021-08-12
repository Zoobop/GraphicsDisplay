#pragma once

#include "DevMathHelpers.h"
#include "DVector3.h"
#include "DVector4.h"

namespace ZM { namespace Math {

//////////////////////////////////////////////////////////////////////////
////                     DevMath - 4x4 Matrix                         ////
//////////////////////////////////////////////////////////////////////////

	struct DMatrix4
	{
		union
		{
			float elements[4 * 4];
			DVector4 columns[4];
		};

		/** Constructors */
		DMatrix4();
		DMatrix4(float diagonal);


		/** Helper Functions */
		DMatrix4& multiply(const DMatrix4& other);

		/** Operator Overloads */
		friend DMatrix4 operator*(DMatrix4 current, const DMatrix4& other);

		DMatrix4& operator*=(const DMatrix4& other);


		/** Static Functions */
		static DMatrix4 Identity();
		static DMatrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static DMatrix4 Perspective(float fov, float aspectRatio, float near, float far);

		static DMatrix4 Translation(const DVector3& translation);
		static DMatrix4 Rotation(float angle, const DVector3& axis);
		static DMatrix4 Scale(const DVector3& scale);
	};

}}