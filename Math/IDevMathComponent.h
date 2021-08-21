#pragma once
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace DevEngine::Math {

	template<typename T, typename GLM>
	__interface IDevMathComponent
	{
		/** Helper Functions */
		virtual T& add(const T& other) = 0;
		virtual T& subtract(const T& other) = 0;
		virtual T& multiply(const T& other) = 0;
		virtual T& divide(const T& other) = 0;

		/** General Functions */
		virtual float Length() const = 0;
		virtual T Normalize() = 0;

		/** GLM Conversion */
		virtual GLM ConvertToGLM() const = 0;

	};

}