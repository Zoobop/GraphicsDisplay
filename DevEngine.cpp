#include "DevEngine.h"
#include <iostream>


ZM::DevEngine::DevEngine()
{
	viewport = new Window();
}

ZM::DevEngine::~DevEngine()
{
	/** Terminates the window */
	glfwTerminate();

	/** Free memory */
	free(viewport);
}

void ZM::DevEngine::EngineInitialize()
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
	glfwDestroyWindow(viewport->window);
}

int ZM::DevEngine::ConstructViewport(unsigned int width, unsigned int height, const char* title)
{
	/** Validate the screen arguments */
	if (width != 0 && height != 0) {
		/** Initializes the GLFW */
		if (!glfwInit()) {
			std::cout << "Could not initialize the GLFW library: Terminating program-" << std::endl;
			return ENGINE_FAIL;
		}
		/** Initializes the viewport window */
		if (viewport->Initialize(width, height, title) == ENGINE_SUCC) {
			std::cout << "Valid viewport for construction: Initializing viewport-" << std::endl;
			return ENGINE_SUCC;
		}
	}
	std::cout << "Invalid screen width or height on construction: Terminating program-" << std::endl;
	return ENGINE_FAIL;
}

bool ZM::DevEngine::WindowExpired()
{
	return glfwWindowShouldClose(viewport->window);
}

void ZM::DevEngine::OnStart()
{

}

void ZM::DevEngine::OnUpdate()
{

}

void ZM::DevEngine::OnTerminate()
{

}
