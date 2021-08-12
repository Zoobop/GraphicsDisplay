#pragma once

namespace ZM { namespace Engine {

	__interface IEngineStartup
	{
		virtual void OnStart();

		virtual void OnUpdate();

		virtual void OnTerminate();
	};
}}
