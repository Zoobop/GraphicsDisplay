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
		OnStart();

		/** Main while loop */
		while (!WindowExpired()) {
			/** Specify the color of the background (normalized RGB) */
			DV_SCREEN_COLOR(screenColor);
			/** Clean the back buffer with the front buffer */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// 		/** Handles the camera controls */
			// 		camera.Inputs(window);
			// 		/** Updates and exports the camera matrix to the Vertex Shader */
			// 		camera.UpdateMatrix(60.0f, 0.1f, 100.0f);
			// 		
			// 		floor.Draw(shaderProgram, camera);
			// 		light.Draw(lightShader, camera);

			/** Update the application every frame */
			OnUpdate();

			/** Swap the back buffer with the front buffer */
			SWAP_BUFFERS(viewport);

			/** Take care of all GLFW events */
			glfwPollEvents();
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
		return viewport->m_Width;
	}

	unsigned int DevEngine::GetScreenHeight() const
	{
		return viewport->m_Height;
	}

	DVector4 DevEngine::GetScreenColor() const
	{
		return screenColor;
	}

	bool DevEngine::WindowExpired()
	{
		return glfwWindowShouldClose(viewport->window);
	}

	void DevEngine::OnStart()
	{

	}

	void DevEngine::OnUpdate()
	{

	}

	void DevEngine::OnTerminate()
	{

	}
}}
