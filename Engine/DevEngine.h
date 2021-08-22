#pragma once

#include "../Engine/Utils/EngineUtils.h"
#include "../Engine/Utils/DebugUtils.h"
#include "../Engine/IEngineStartup.h"
#include "../Graphics/Window.h"
#include "../Math/DevMath.h"

using namespace DevEngine::Math;
using namespace DevEngine::Graphics;

namespace DevEngine::Engine {

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

	public:
		/** Display screen */
		class Window* m_Viewport;
		/** Main camera */
		class Camera m_MainCamera;

	private:
		/** Fill screen color */
		DVector4 m_ScreenColor = DevCOLOR_BLACK;	



	/** Override interface functions */
	public:
		/** Function called at the start of the application before the update function */
		virtual void OnInitialize() override;
		/** Function called each frame */
		virtual void OnUpdate() override;
		/** Function called at the end of the application after the window should close */
		virtual void OnTerminate() override;

	};
}

