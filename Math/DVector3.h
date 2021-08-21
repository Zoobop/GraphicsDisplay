#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "IDevMathComponent.h"

namespace DevEngine::Math {

//////////////////////////////////////////////////////////////////////////
////                     DevMath - 3D Vector                          ////
//////////////////////////////////////////////////////////////////////////

	struct DVector3 : public IDevMathComponent<DVector3, glm::vec3>
	{
		/** Elements */
		float x, y, z;


		/** Constructors */
		DVector3() = default;
		DVector3(const glm::vec3& other);
		DVector3(const float* values);
		DVector3(const float& x, const float& y, const float& z);


		/** Helper Functions */
		DVector3& add(const DVector3& other);
		DVector3& add(const glm::vec3& other);
		DVector3& subtract(const DVector3& other);
		DVector3& multiply(const DVector3& other);
		DVector3& multiply(const float& other);
		DVector3& divide(const DVector3& other);


		/** Operator Overloads */
		friend DVector3 operator+(DVector3 current, const DVector3& other);
		friend DVector3 operator-(DVector3 current, const DVector3& other);
		friend DVector3 operator*(DVector3 current, const DVector3& other);
		friend DVector3 operator*(DVector3 current, const float& other);
		friend DVector3 operator*(float current, const DVector3& other);
		friend DVector3 operator/(DVector3 current, const DVector3& other);

		friend DVector3 operator-(const DVector3& current);

		DVector3& operator+=(const DVector3& other);
		DVector3& operator+=(const glm::vec3& other);
		DVector3& operator-=(const DVector3& other);
		DVector3& operator*=(const DVector3& other);
		DVector3& operator*=(const float& other);
		DVector3& operator/=(const DVector3& other);

		bool operator!=(const DVector3& other);
		bool operator==(const DVector3& other);
		bool operator<=(const DVector3& other);
		bool operator>=(const DVector3& other);
		bool operator<=(const float& other);
		bool operator>=(const float& other);

		void operator=(const DVector3& other);
		void operator=(const glm::vec3& other);

		friend std::ostream& operator<<(std::ostream& stream, const DVector3& vector);


		/** Conversions to GLM */
		glm::vec3 ConvertToGLM() const override;


		/** DevMathComponent Overrides */
		float Length() const override;
		DVector3 Normalize() override;


		/** Static Functions */
		static DVector3 Make(const float* values);
		static DVector3 Zero();
		static DVector3 Identity();

	};

}

