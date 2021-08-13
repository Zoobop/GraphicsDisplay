#include "Engine/DevEngine.h"
#include "Graphics/Camera.h"

class EngineTest : public ZM::Engine::DevEngine
{
public:

	Mesh floor, light;

	void OnInitialize() override
	{
		ENGINE_LOG("Start");
		SetScreenColor(DevCOLOR_DARK_RED);
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

const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
	Vertex{DVector3(-1.0f, 0.0f,  1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(0.0f, 0.0f)},
	Vertex{DVector3(-1.0f, 0.0f, -1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(0.0f, 1.0f)},
	Vertex{DVector3(1.0f, 0.0f, -1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(1.0f, 1.0f)},
	Vertex{DVector3(1.0f, 0.0f,  1.0f), DVector3(0.0f, 1.0f, 0.0f), DVector3(1.0f, 1.0f, 1.0f), DVector2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{DVector3(-0.1f, -0.1f,  0.1f)},
	Vertex{DVector3(-0.1f, -0.1f, -0.1f)},
	Vertex{DVector3(0.1f, -0.1f, -0.1f)},
	Vertex{DVector3(0.1f, -0.1f,  0.1f)},
	Vertex{DVector3(-0.1f,  0.1f,  0.1f)},
	Vertex{DVector3(-0.1f,  0.1f, -0.1f)},
	Vertex{DVector3(0.1f,  0.1f, -0.1f)},
	Vertex{DVector3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

#include <filesystem>
namespace fs = std::filesystem;

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/Textures/";


	// Texture data
	Texture textures[]
	{
		Texture("planks.png", TT_DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", TT_SPECULAR, 1, GL_RED, GL_UNSIGNED_BYTE)
	};



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("Graphics/Shaders/default.vert", "Graphics/Shaders/default.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	Mesh floor(MESH_PLANE);


	// Shader for light cube
	Shader lightShader("Graphics/Shaders/light.vert", "Graphics/Shaders/light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Crate light mesh
	Mesh light(MESH_CUBE);





	DVector4 lightColor = DVector4::Identity();
	DVector3 lightPos(0.5f, 0.5f, 0.5f);
	DMatrix4 lightModel(1.0f);
	lightModel = DMatrix4::Translate(lightModel, lightPos);

	DVector3 objectPos = DVector3::Zero();
	DMatrix4 objectModel(1.0f);
	objectModel = DMatrix4::Translate(objectModel, objectPos);


	lightShader.Activate();
	lightShader.SetUniformMat4("model", lightModel);
	lightShader.SetUniformVec4("lightColor", lightColor);

	shaderProgram.Activate();
	shaderProgram.SetUniformMat4("model", objectModel);
	shaderProgram.SetUniformVec4("lightColor", lightColor);
	shaderProgram.SetUniformVec3("lightPos", lightPos);





	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, DVector3(0.0f, 1.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.UpdateMatrix(60.0f, 0.1f, 100.0f);


		// Draws different meshes
		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}