#include "Camera.h"

namespace DevEngine::Graphics {

	Camera::Camera(unsigned int width, unsigned int height, DVector3 position)
		: m_Width(width), m_Height(height), m_Position(position)
	{
	}

	Camera::Camera()
	{
	}

	void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		DMatrix4 view(1.0f);
		DMatrix4 projection(1.0f);

		view = glm::lookAt(m_Position.ConvertToGLM(), m_Position.ConvertToGLM() + m_Orientation.ConvertToGLM(), m_Up.ConvertToGLM());
		projection = glm::perspective(glm::radians(FOVdeg), (float)(m_Width / m_Height), nearPlane, farPlane);

		m_CameraMatrix = projection * view;
	}

	void Camera::Matrix(Shader& shader, const char* uniform)
	{
		shader.SetUniformMat4(uniform, m_CameraMatrix);
	}

	void Camera::Inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_Position += m_Speed * m_Orientation;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_Position += m_Speed * -glm::normalize(glm::cross(m_Orientation.ConvertToGLM(), m_Up.ConvertToGLM()));
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_Position += m_Speed * -m_Orientation;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation.ConvertToGLM(), m_Up.ConvertToGLM()));
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

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
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

			glm::vec3 newOrientation = glm::rotate(m_Orientation.ConvertToGLM(), (float)RAD2DEG(-rotX), glm::normalize(glm::cross(m_Orientation.ConvertToGLM(), m_Up.ConvertToGLM())));

			// Decides whether or not the next vertical Orientation is legal or not
			if (abs(glm::angle(newOrientation, m_Up.ConvertToGLM()) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				m_Orientation = newOrientation;
			}

			// Rotates the Orientation left and right
			m_Orientation = glm::rotate(m_Orientation.ConvertToGLM(), glm::radians(-rotY), m_Up.ConvertToGLM());

			glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));

		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_FirstClick = true;
		}
	}
}
