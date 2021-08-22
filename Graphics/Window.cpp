#include "Window.h"
#include "../Engine/Utils/DebugUtils.h"
#include "../Engine/Utils/EngineUtils.h"

#include "../Math/DMatrix4.h"

namespace ZM { namespace Graphics {

	void ResizeWindow(GLFWwindow* window, int width, int height);
	void OnMouseCursorMoved(GLFWwindow* window, double xPos, double yPos);
	void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);
	void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

	Window::Window()
	{
		m_Title = "";
		m_Width = 0;
		m_Height = 0;
		m_MouseX = 0.0;
		m_MouseY = 0.0;

		for (auto i = 0; i < MAX_KEYS; i++) {
			m_Keys[i] = false;
		}
		for (auto i = 0; i < MAX_BUTTONS; i++) {
			m_MouseButtons[i] = false;
		}

		m_Window = NULL;
	}

	Window::~Window()
	{
		free(m_Window);
		glfwTerminate();
	}

	int Window::Initialize(unsigned int width, unsigned int height, const char* title)
	{
		/** Cache the window variables */
		m_Title = title;
		m_Width = width;
		m_Height = height;

		/** Initialize keys */
		for (auto i = 0; i < MAX_KEYS; i++) {
			m_Keys[i] = false;
		}

		/** Initialize buttons */
		for (auto i = 0; i < MAX_BUTTONS; i++) {
			m_MouseButtons[i] = false;
		}

		/** Tell GLFW what version of OpenGL we are using */
		/** In this case we are using OpenGL 3.3 */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		/** Tell GLFW we are using the CORE profile */
		/** So that means we only have the modern functions */
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/** Create a GLFWwindow object of width by height pixels, naming it "Test Window" */
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		/** Null check the window */
		if (m_Window == NULL) {
			ENGINE_LOG("Failed to create GLFW window: Terminating program-");
			glfwTerminate();
			return ENGINE_INIT_FAIL;
		}
		/** Introduce the window into the current context */
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, ResizeWindow);
		glfwSetKeyCallback(m_Window, OnKeyPressed);
		glfwSetMouseButtonCallback(m_Window, OnMouseButtonPressed);
		glfwSetCursorPosCallback(m_Window, OnMouseCursorMoved);

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
  			n_TEXTURE_DEFAULT_DIFFUSE,
  			n_TEXTURE_DEFAULT_SPECULAR,
  		};
  
  		/** Generates Shader object using shaders default.vert and default.frag */
  		shaderProgram = Shader("Graphics/Shaders/default.vert", "Graphics/Shaders/default.frag");
  		std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
  		//Mesh floor(verts, ind, tex);
  		Mesh floor(MESH_PLANE, tex);
  
  		/** Shader for the Light object */
  		lightShader = Shader("Graphics/Shaders/light.vert", "Graphics/Shaders/light.frag");
  		//Mesh light(lightVerts, lightInd, tex);
  		Mesh light(MESH_CUBE, tex);

  		/** Enables the depth buffer */
  		glEnable(GL_DEPTH_TEST);
  
  		lightShader.Activate();
  		glUniformMatrix4fv(glGetUniformLocation(lightShader.GetShaderID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
  		glUniform4f(glGetUniformLocation(lightShader.GetShaderID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  		shaderProgram.Activate();
  		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderID(), "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
  		glUniform4f(glGetUniformLocation(shaderProgram.GetShaderID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  		glUniform3f(glGetUniformLocation(shaderProgram.GetShaderID(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		return 0;
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);
	}

	bool Window::WindowExpired() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::IsKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS) {
			return false;
		}

		return m_Keys[keycode];
	}


	bool Window::IsMouseButtonPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_BUTTONS) {
			return false;
		}

		return m_MouseButtons[keycode];
	}

	void Window::GetMousePosition(double& xPos, double& yPos) const
	{
		xPos = m_MouseX;
		yPos = m_MouseY;
	}

	void ResizeWindow(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* screen = (Window*)glfwGetWindowUserPointer(window);
		screen->m_Keys[key] = action != GLFW_RELEASE;
	}

	void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods)
	{
		Window* screen = (Window*)glfwGetWindowUserPointer(window);
		screen->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void OnMouseCursorMoved(GLFWwindow* window, double xPos, double yPos)
	{
		Window* screen = (Window*)glfwGetWindowUserPointer(window);
		screen->m_MouseX = xPos;
		screen->m_MouseY = yPos;
	}

}}
