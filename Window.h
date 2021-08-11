#pragma once
#include "Mesh.h"

#define DV_COLOR_WHITE			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define DV_COLOR_BLACK			glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)
#define DV_COLOR_RED			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
#define DV_COLOR_GREEN			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
#define DV_COLOR_BLUE			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
#define DV_COLOR_DARK_RED		glm::vec4(0.17f, 0.07f, 0.13f, 1.0f)
#define DV_COLOR_DARK_GREEN		glm::vec4(0.13f, 0.17f, 0.07f, 1.0f)
#define DV_COLOR_DARK_BLUE		glm::vec4(0.07f, 0.13f, 0.17f, 1.0f)

#define DV_SCREEN_COLOR(color)		glClearColor(color.x, color.y, color.z, color.w)

class Window
{
public:
	Window();
	~Window();

	int Initialize(unsigned int width, unsigned int height, const char* title);

public:

	GLFWwindow* window;

	const char* m_Title;
	unsigned int m_Width;
	unsigned int m_Height;

};
