#pragma once

namespace ZM { namespace Engine {

	__interface IEngineStartup
	{
		virtual void OnInitialize();

		virtual void OnUpdate();

		virtual void OnTerminate();
	};
}}
