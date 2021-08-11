#include "Window.h"

Window::Window()
{
	m_Title = "";
	m_Width = 0;
	m_Height = 0;

	window = NULL;
}

Window::~Window()
{
	free(window);
}

int Window::Initialize(unsigned int width, unsigned int height, const char* title)
{
	/** Cache the window variables */
	m_Title = title;
	m_Width = width;
	m_Height = height;

	/** Tell GLFW what version of OpenGL we are using */
	/** In this case we are using OpenGL 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	/** Tell GLFW we are using the CORE profile */
	/** So that means we only have the modern functions */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/** Create a GLFWwindow object of width by height pixels, naming it "Test Window" */
	window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	/** Null check the window */
	if (window == NULL) {
		std::cout << "Failed to create GLFW window: Terminating program-" << std::endl;
		glfwTerminate();
		return -1;
	}
	/** Introduce the window into the current context */
	glfwMakeContextCurrent(window);

	/** Load GLAD so it configures OpenGL */
	gladLoadGL();

	/** Specify the viewport of OpenGL in the Window */
	/** In this case, the viewport goes from x = 0, y = 0, to x = width, y = height */
	glViewport(0, 0, m_Width, m_Height);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	/** Texture */
	Texture textures[]{
		Texture("planks.png", TT_DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", TT_SPECULAR, 1, GL_RED, GL_UNSIGNED_BYTE),
	};

	/** Generates Shader object using shaders default.vert and default.frag */
	Shader shaderProgram("default.vert", "default.frag");
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	//Mesh floor(verts, ind, tex);
	Mesh floor(MESH_PLANE, tex);

	/** Shader for the Light object */
	Shader lightShader("light.vert", "light.frag");
	//Mesh light(lightVerts, lightInd, tex);
	Mesh light(MESH_CUBE, tex);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	/** Enables the depth buffer */
	glEnable(GL_DEPTH_TEST);

	/** Create camera object */
	Camera camera(m_Width, m_Height, glm::vec3(0.0f, 1.0f, 2.0f));



	/** Delete all the objects we created */
	lightShader.Delete();
	shaderProgram.Delete();
	return 0;
}
