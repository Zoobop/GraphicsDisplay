#pragma once
#include "Model.h"

#define DevCOLOR_WHITE			DVector4(1.0f, 1.0f, 1.0f, 1.0f)
#define DevCOLOR_BLACK			DVector4(0.0f, 0.0f, 0.0f, 0.0f)
#define DevCOLOR_RED			DVector4(1.0f, 0.0f, 0.0f, 1.0f)
#define DevCOLOR_GREEN			DVector4(0.0f, 1.0f, 0.0f, 1.0f)
#define DevCOLOR_BLUE			DVector4(0.0f, 0.0f, 1.0f, 1.0f)
#define DevCOLOR_DARK_RED		DVector4(0.17f, 0.07f, 0.13f, 1.0f)
#define DevCOLOR_DARK_GREEN		DVector4(0.13f, 0.17f, 0.07f, 1.0f)
#define DevCOLOR_DARK_BLUE		DVector4(0.07f, 0.13f, 0.17f, 1.0f)

#define DevSCREEN_COLOR(color)		glClearColor(color.x, color.y, color.z, color.w)

#define MAX_KEYS		1024
#define MAX_BUTTONS		32

namespace DevEngine::Graphics {

	class Window
	{
	public:
		Window();
		~Window();

		int Initialize(unsigned int width, unsigned int height, const char* title);

		void Clear() const;
		void Update();
		bool WindowExpired() const;

		inline unsigned int GetScreenWidth() const { return m_Width; }
		inline unsigned int GetScreenHeight() const { return m_Height; }
		inline GLFWwindow* GetWindow() const { return m_Window; }

		bool IsKeyPressed(unsigned int keycode) const;
		bool IsMouseButtonPressed(unsigned int keycode) const;
		void GetMousePosition(double& xPos, double& yPos) const;

	private:

		friend static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);
		friend static void OnMouseCursorMoved(GLFWwindow* window, double xPos, double yPos);

	private:

		GLFWwindow* m_Window;

		const char* m_Title;
		int m_Width, m_Height;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double m_MouseX, m_MouseY;

	public:
		Shader shaderProgram, lightShader;

	};

	void ResizeWindow(GLFWwindow* window, int width, int height);
}