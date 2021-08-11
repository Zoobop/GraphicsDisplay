#include "DevEngine.h"

class EngineTest : public ZM::DevEngine
{
public:
	void OnStart() override
	{
		std::cout << "Start" << std::endl;
	}

	void OnUpdate() override
	{
		std::cout << "Update" << std::endl;
	}

	void OnTerminate() override
	{
		std::cout << "Terminate" << std::endl;
	}

};

int main()
{
	EngineTest engine;
	if (engine.ConstructViewport(800, 800, "Engine Startup Test") == ENGINE_SUCC)
		engine.EngineInitialize();

	return 0;
}