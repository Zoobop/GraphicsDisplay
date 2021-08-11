#pragma once

#include <iostream>

namespace ZM { namespace Math {

//////////////////////////////////////////////////////////////////////////
////                             DevMath                              ////
//////////////////////////////////////////////////////////////////////////

	struct DVector2
	{
		float x, y;

		DVector2();
		DVector2(const float& x, const float& y);

		DVector2& add(const DVector2& other);
		DVector2& subtract(const DVector2& other);
		DVector2& multiply(const DVector2& other);
		DVector2& divide(const DVector2& other);

		friend DVector2& operator+(DVector2& current, const DVector2& other);
		friend DVector2& operator-(DVector2& current, const DVector2& other);
		friend DVector2& operator*(DVector2& current, const DVector2& other);
		friend DVector2& operator/(DVector2& current, const DVector2& other);

		DVector2& operator+=(const DVector2& other);
		DVector2& operator-=(const DVector2& other);
		DVector2& operator*=(const DVector2& other);
		DVector2& operator/=(const DVector2& other);

		bool operator!=(const DVector2& other);
		bool operator==(const DVector2& other);

		void operator=(const DVector2& other);

		std::ostream& operator<<(std::ostream& stream);


	};

	struct DVector3
	{
		float x, y, z;

		DVector3();
		DVector3(const float& x, const float& y, const float& z);


	};
}}