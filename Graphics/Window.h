#pragma once
#include "Mesh.h"

#define DV_COLOR_WHITE			DVector4(1.0f, 1.0f, 1.0f, 1.0f)
#define DV_COLOR_BLACK			DVector4(0.0f, 0.0f, 0.0f, 0.0f)
#define DV_COLOR_RED			DVector4(1.0f, 0.0f, 0.0f, 1.0f)
#define DV_COLOR_GREEN			DVector4(0.0f, 1.0f, 0.0f, 1.0f)
#define DV_COLOR_BLUE			DVector4(0.0f, 0.0f, 1.0f, 1.0f)
#define DV_COLOR_DARK_RED		DVector4(0.17f, 0.07f, 0.13f, 1.0f)
#define DV_COLOR_DARK_GREEN		DVector4(0.13f, 0.17f, 0.07f, 1.0f)
#define DV_COLOR_DARK_BLUE		DVector4(0.07f, 0.13f, 0.17f, 1.0f)

#define DV_SCREEN_COLOR(color)		glClearColor(color.x, color.y, color.z, color.w)

namespace ZM { namespace Graphics {

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
}}