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
		Camera(unsigned int width, unsigned int height, glm::vec3 position);

		/** Updates and exports the camera matrix to the Vertex Shader */
		void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		/** Handles the camera controls */
		void Inputs(GLFWwindow* m_Window);

		void Create(unsigned int width, unsigned int height, glm::vec3 position);

	public:

		/** Stores the main three vectors of the camera */
		glm::vec3 m_Position;
		glm::vec3 m_Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 m_CameraMatrix = glm::mat4(1.0f);

		/** Adjust the speed of the camera and it's sensitivity when looking around */
		float m_Speed = 0.01f;
		float m_Sensitivity = 100.0f;

	protected:

		/** Stores the width and height of the window */
		unsigned int m_Width;
		unsigned int m_Height;

		/** Prevents the camera from jumping around when first clicking left click */
		bool m_FirstClick = true;

		const float m_DefaultSpeed = 0.01f;
		const float m_FastSpeed = 0.04f;
	};

}
