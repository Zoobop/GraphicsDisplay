#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace DevEngine::Math {

//////////////////////////////////////////////////////////////////////////
////                     DevMath - 4D Vector                          ////
//////////////////////////////////////////////////////////////////////////

	struct DVector4
	{
		float x, y, z, w;

		DVector4() = default;
		DVector4(const float& x, const float& y, const float& z, const float& w);

		DVector4& add(const DVector4& other);
		DVector4& subtract(const DVector4& other);
		DVector4& multiply(const DVector4& other);
		DVector4& divide(const DVector4& other);

		friend DVector4 operator+(DVector4 current, const DVector4& other);
		friend DVector4 operator-(DVector4 current, const DVector4& other);
		friend DVector4 operator*(DVector4 current, const DVector4& other);
		friend DVector4 operator/(DVector4 current, const DVector4& other);

		DVector4& operator+=(const DVector4& other);
		DVector4& operator-=(const DVector4& other);
		DVector4& operator*=(const DVector4& other);
		DVector4& operator/=(const DVector4& other);

		bool operator!=(const DVector4& other);
		bool operator==(const DVector4& other);

		void operator=(const DVector4& other);
		void operator=(const glm::vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, const DVector4& vector);

		static DVector4 Identity();
	};

}