#pragma once

namespace DevEngine {

	__interface IEngineStartup
	{
		virtual void OnInitialize();

		virtual void OnUpdate();

		virtual void OnTerminate();
	};
}
