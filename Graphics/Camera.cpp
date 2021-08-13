#include "Camera.h"

namespace ZM { namespace Graphics {

	Camera::Camera(unsigned int width, unsigned int height, DVector3 position)
	{
		this->width = width;
		this->height = height;

		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
	}

	Camera::Camera()
	{

	}

	void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
	{
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(position, position + orientation, up);
		projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

		cameraMatrix = projection * view;
	}

	void Camera::Matrix(Shader& shader, const char* uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.GetShaderID(), uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}

	void Camera::Inputs(GLFWwindow* m_Window)
	{
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
			position += speed * orientation;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
			position += speed * -glm::normalize(glm::cross(orientation, up));
		}

		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
			position += speed * -orientation;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
			position += speed * glm::normalize(glm::cross(orientation, up));
		}

		if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			position += speed * up;
		}

		if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			position += speed * -up;
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

			glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

			if (!(glm::angle(newOrientation, up) <= glm::radians(5.0f) or glm::angle(newOrientation, -up) <= glm::radians(5.0f))) {
				orientation = newOrientation;
			}

			orientation = glm::rotate(orientation, glm::radians(-rotY), up);

			glfwSetCursorPos(m_Window, (width / 2), (height / 2));

		}
		else if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			firstClick = true;
		}
	}
}}