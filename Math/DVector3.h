#pragma once
#include <iostream>

namespace ZM { namespace Math {

//////////////////////////////////////////////////////////////////////////
////                     DevMath - 3D Vector                          ////
//////////////////////////////////////////////////////////////////////////

	struct DVector3
	{
		float x, y, z;

		DVector3() = default;
		DVector3(const float& x, const float& y, const float& z);

		DVector3& add(const DVector3& other);
		DVector3& subtract(const DVector3& other);
		DVector3& multiply(const DVector3& other);
		DVector3& divide(const DVector3& other);

		friend DVector3 operator+(DVector3 current, const DVector3& other);
		friend DVector3 operator-(DVector3 current, const DVector3& other);
		friend DVector3 operator*(DVector3 current, const DVector3& other);
		friend DVector3 operator/(DVector3 current, const DVector3& other);

		DVector3& operator+=(const DVector3& other);
		DVector3& operator-=(const DVector3& other);
		DVector3& operator*=(const DVector3& other);
		DVector3& operator/=(const DVector3& other);

		bool operator!=(const DVector3& other);
		bool operator==(const DVector3& other);

		void operator=(const DVector3& other);

		friend std::ostream& operator<<(std::ostream& stream, const DVector3& vector);
	};

}}

