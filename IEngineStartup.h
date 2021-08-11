#pragma once

__interface IEngineStartup
{
	virtual void OnStart();

	virtual void OnUpdate();

	virtual void OnTerminate();
};