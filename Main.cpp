#include "Engine/DevEngine.h"
#include "Graphics/Camera.h"

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
};

GLuint vbo;

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

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Shader shader("Graphics/Shaders/basic.vert", "Graphics/Shaders/basic.frag");
	shader.Activate();

// 
// 	while (!ENGINE_GRAPHICS_INITIALIZED)
// 	{
// 		glDrawArrays(GL_TRIANGLES, 0, 6);
// 	}

	return 0;
}