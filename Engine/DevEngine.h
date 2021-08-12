#pragma once

#include "../Engine/Utils/EngineUtils.h"
#include "../Engine/IEngineStartup.h"
#include "../Graphics/Window.h"
#include "../Math/DevMath.h"

using namespace ZM::Math;
using namespace ZM::Graphics;

namespace ZM { namespace Engine {

#define ENGINE_INIT_FAIL	-1
#define ENGINE_INIT_SUCC	 0

#define ENGINE_GRAPHICS_INITIALIZED				glfwInit()
#define ENGINE_GRAPHICS_TERMINATE(viewport)		glfwDestroyWindow(viewport->window)

#define SWAP_BUFFERS(screen)					glfwSwapBuffers(screen->window)

//////////////////////////////////////////////////////////////////////////
////                          Engine Base                             ////
//////////////////////////////////////////////////////////////////////////

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

		/** Changes the color of the screen */
		void SetScreenColor(DVector4 color);

		/** Returns the screen width */
		unsigned int GetScreenWidth() const;
		/** Returns the screen height */
		unsigned int GetScreenHeight() const;
		/** Returns the screen color */
		DVector4 GetScreenColor() const;

	private:
		/** Checks for when the viewport/window closes */
		bool WindowExpired();

	public:
		/** Display screen */
		class Window* viewport;

	private:
		/** Fill screen color */
		DVector4 screenColor = DV_COLOR_BLACK;	



	/** Override interface functions */
	public:
		/** Function called at the start of the application before the update function */
		virtual void OnStart() override;
		/** Function called each frame */
		virtual void OnUpdate() override;
		/** Function called at the end of the application after the window should close */
		virtual void OnTerminate() override;

	};
}}

