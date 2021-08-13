#include "DevEngine.h"
#include <iostream>

namespace ZM { namespace Engine {

	DevEngine::DevEngine()
	{
		viewport = new Window();
	}

	DevEngine::~DevEngine()
	{
		/** Terminates the window */
		glfwTerminate();

		/** Free memory */
		free(viewport);
	}

	void DevEngine::EngineInitialize()
	{
		/** Start function */
		OnInitialize();

		/** Main while loop */
		while (!viewport->WindowExpired()) {
			/** Specify the color of the background (normalized RGB) */
			DevSCREEN_COLOR(screenColor);
			/** Clean the back buffer with the front buffer */
			viewport->Clear();

			/** Update the application every frame */
			OnUpdate();

			/** Swap the back buffer with the front buffer and take care of all GLFW events */
			viewport->Update();
		}

		/** Application and screen termination */
		OnTerminate();

		/** Delete window before ending the program */
		ENGINE_GRAPHICS_TERMINATE(viewport);
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
			if (viewport->Initialize(width, height, title) == ENGINE_INIT_SUCC) {
				camera = Camera(width, height, DVector3::Zero());
				ENGINE_LOG("Valid viewport for construction: Initializing viewport-");
				return ENGINE_INIT_SUCC;
			}
		}
		ENGINE_LOG("Invalid screen width or height on construction: Terminating program-");
		return ENGINE_INIT_FAIL;
	}

	void DevEngine::SetScreenColor(DVector4 color)
	{
		screenColor = color;
	}

	unsigned int DevEngine::GetScreenWidth() const
	{
		return viewport->GetScreenWidth();
	}

	unsigned int DevEngine::GetScreenHeight() const
	{
		return viewport->GetScreenHeight();
	}

	DVector4 DevEngine::GetScreenColor() const
	{
		return screenColor;
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
}}
