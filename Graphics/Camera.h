#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../Math/DVector3.h"

#include "Shader.h"

using namespace DevEngine::Math;

namespace DevEngine::Graphics {

	class Camera
	{
	public:
		/** Camera constructor */
		Camera();
		Camera(unsigned int width, unsigned int height, DVector3 position);

		/** Updates and exports the camera matrix to the Vertex Shader */
		void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		/** Handles the camera controls */
		void Inputs(GLFWwindow* m_Window);

	public:

		/** Stores the main three vectors of the camera */
		DVector3 m_Position;
		DVector3 m_Orientation = DVector3(0.0f, 0.0f, -1.0f);
		DVector3 m_Up = DVector3(0.0f, 1.0f, 0.0f);
		DMatrix4 m_CameraMatrix = DMatrix4(1.0f);

		/** Adjust the speed of the camera and it's sensitivity when looking around */
		float m_Speed = 0.01f;
		float m_Sensitivity = 100.0f;

	protected:

		/** Stores the width and height of the window */
		unsigned int m_Width;
		unsigned int m_Height;

		/** Prevents the camera from jumping around when first clicking left click */
		bool m_FirstClick = true;

		float m_DefaultSpeed = 0.01f;
		float m_FastSpeed = 0.04f;
	};

}
