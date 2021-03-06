#pragma once

namespace DevEngine::Engine {

	__interface IEngineStartup
	{
		virtual void OnInitialize();

		virtual void OnUpdate();

		virtual void OnTerminate();
	};
}
