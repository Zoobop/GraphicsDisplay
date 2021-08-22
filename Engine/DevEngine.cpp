#include "DevEngine.h"
#include <iostream>

namespace DevEngine::Engine {

	DevEngine::DevEngine()
	{
		m_Viewport = new Window();
	}

	DevEngine::~DevEngine()
	{
		/** Terminates the window */
		glfwTerminate();

		/** Free memory */
		free(m_Viewport);
	}

	void DevEngine::EngineInitialize()
	{
		/** Start function */
		OnInitialize();

		/** Main while loop */
		while (!m_Viewport->WindowExpired()) {
			/** Specify the color of the background (normalized RGB) */
			DevSCREEN_COLOR(m_ScreenColor);
			/** Clean the back buffer with the front buffer */
			m_Viewport->Clear();

			m_MainCamera.Inputs(m_Viewport->GetWindow());
			m_MainCamera.UpdateMatrix(60.0f, 0.01f, 100.0f);

			/** Update the application every frame */
			OnUpdate();

			/** Swap the back buffer with the front buffer and take care of all GLFW events */
			m_Viewport->Update();
		}

		/** Application and screen termination */
		OnTerminate();

		/** Delete window before ending the program */
		ENGINE_GRAPHICS_TERMINATE(m_Viewport);
	}

	int DevEngine::ConstructViewport(unsigned int width, unsigned int height, const char* title)
	{
		/** Validate the screen arguments */
		if (width != 0 && height != 0) {
			/** Initializes the GLFW */
			if (!ENGINE_GRAPHICS_INITIALIZED) {
				ENGINE_LOG("Could not initialize the GLFW library: Terminating program-");
				return ENGINE_INIT_FAIL;
			}
			/** Initializes the viewport window */
			if (m_Viewport->Initialize(width, height, title) == ENGINE_INIT_SUCC) {
				m_MainCamera.Create(width, height, glm::vec3(0.0f, 1.0f, 3.0f));
				ENGINE_LOG("Valid viewport for construction: Initializing viewport-");
				return ENGINE_INIT_SUCC;
			}
		}
		ENGINE_LOG("Invalid screen width or height on construction: Terminating program-");
		return ENGINE_INIT_FAIL;
	}

	void DevEngine::SetScreenColor(DVector4 color)
	{
		m_ScreenColor = color;
	}

	unsigned int DevEngine::GetScreenWidth() const
	{
		return m_Viewport->GetScreenWidth();
	}

	unsigned int DevEngine::GetScreenHeight() const
	{
		return m_Viewport->GetScreenHeight();
	}

	DVector4 DevEngine::GetScreenColor() const
	{
		return m_ScreenColor;
	}

	void DevEngine::OnInitialize()
	{

	}

	void DevEngine::OnUpdate()
	{

	}

	void DevEngine::OnTerminate()
	{

	}
}
