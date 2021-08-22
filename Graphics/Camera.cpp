#include "Camera.h"

namespace DevEngine::Graphics {

	Camera::Camera(unsigned int width, unsigned int height, DVector3 position)
	{
		this->width = width;
		this->height = height;

		this->m_Position.x = position.x;
		this->m_Position.y = position.y;
		this->m_Position.z = position.z;
	}

	Camera::Camera()
	{

	}

	void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(m_Position.ConvertToGLM(), m_Position.ConvertToGLM() + m_Orientation, m_Up);
		projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

		m_CameraMatrix = projection * view;
	}

	void Camera::Matrix(Shader& shader, const char* uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), uniform), 1, GL_FALSE, glm::value_ptr(m_CameraMatrix));
	}

	void Camera::Inputs(GLFWwindow* m_Window)
	{
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
			m_Position += speed * m_Orientation;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
			m_Position += speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
		}

		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
			m_Position += speed * -m_Orientation;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
			m_Position += speed * glm::normalize(glm::cross(m_Orientation, m_Up));
		}

		if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			m_Position += speed * m_Up;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			m_Position += speed * -m_Up;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			speed = fastSpeed;
		}
		else if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
			speed = defaultSpeed;
		}

		if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (firstClick) {
				glfwSetCursorPos(m_Window, (width / 2), (height / 2));
				firstClick = false;
			}

			double mouseX;
			double mouseY;
			glfwGetCursorPos(m_Window, &mouseX, &mouseY);

			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

			glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

			if (!(glm::angle(newOrientation, m_Up) <= glm::radians(5.0f) or glm::angle(newOrientation, -m_Up) <= glm::radians(5.0f))) {
				m_Orientation = newOrientation;
			}

			m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

			glfwSetCursorPos(m_Window, (width / 2), (height / 2));

		}
		else if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	}
}
