#include "Engine/DevEngine.h"
#include "Graphics/Camera.h"

class EngineTest : public ZM::Engine::DevEngine
{
public:
	void OnStart() override
	{
		ENGINE_LOG("Start");
	}

	void OnUpdate() override
	{
		//ENGINE_LOG("Update");
	}

	void OnTerminate() override
	{
		ENGINE_LOG("Terminate");
	}

};

int main()
{
	EngineTest engine;
	if (engine.ConstructViewport(800, 800, "Engine Startup Test") == ENGINE_INIT_SUCC)
		engine.EngineInitialize();

	return 0;
}