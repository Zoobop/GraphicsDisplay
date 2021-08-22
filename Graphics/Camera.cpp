#include "Camera.h"

namespace DevEngine::Graphics {

	Camera::Camera()
	{
	}

	Camera::Camera(unsigned int width, unsigned int height, glm::vec3 position)
		: m_Width(width), m_Height(height), m_Position(position)
	{
	}

	void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
		projection = glm::perspective(glm::radians(FOVdeg), (float)(m_Width / m_Height), nearPlane, farPlane);

		m_CameraMatrix = projection * view;
	}

	void Camera::Matrix(Shader& shader, const char* uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), uniform), 1, GL_FALSE, glm::value_ptr(m_CameraMatrix));
	}

	void Camera::Inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_Position += m_Speed * m_Orientation;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_Position += m_Speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_Position += m_Speed * -m_Orientation;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation, m_Up));
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			m_Position += m_Speed * m_Up;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			m_Position += m_Speed * -m_Up;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			m_Speed = m_FastSpeed;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
			m_Speed = m_DefaultSpeed;
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (m_FirstClick) {
				glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
				m_FirstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotX = m_Sensitivity * (float)(mouseY - (m_Height / 2)) / m_Height;
			float rotY = m_Sensitivity * (float)(mouseX - (m_Height / 2)) / m_Height;

			glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

			if (!(glm::angle(newOrientation, m_Up) <= glm::radians(5.0f) or glm::angle(newOrientation, -m_Up) <= glm::radians(5.0f))) {
				m_Orientation = newOrientation;
			}

			m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

			glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));

		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_FirstClick = true;
		}
	}

	void Camera::Create(unsigned int width, unsigned int height, glm::vec3 position)
	{
		m_Width = width;
		m_Height = height;
		m_Position = position;
	}
}
