#pragma once
#include "IEngineStartup.h"
#include "DevMath.h"
#include "Window.h"

namespace ZM 
{

//////////////////////////////////////////////////////////////////////////
////                          Engine Base                             ////
//////////////////////////////////////////////////////////////////////////

#define ENGINE_FAIL		-1
#define ENGINE_SUCC		 0

#define SWAP_BUFFERS(screen) glfwSwapBuffers(screen->window)

	/** Base engine implementation */
	class DevEngine : public IEngineStartup
	{
	public:
		DevEngine();
		~DevEngine();

		/** Starts up the DevEngine */
		void EngineInitialize();

		/** Creates the screen with the specified parameters */
		int ConstructViewport(unsigned int width, unsigned int height, const char* title);

	public:
		/** Display screen */
		class Window* viewport;
		/** Fill screen color */
		glm::vec4 screenColor = DV_COLOR_BLACK;

	private:
		/** Checks for when the viewport/window closes */
		bool WindowExpired();

		/** Override interface functions */
	public:
		/** Function called at the start of the application before the update function */
		virtual void OnStart() override;
		/** Function called each frame */
		virtual void OnUpdate() override;
		/** Function called at the end of the application after the window should close */
		virtual void OnTerminate() override;

	};
}

