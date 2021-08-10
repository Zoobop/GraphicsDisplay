#include "Mesh.h"


#define zCOLOR_WHITE		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
#define zCOLOR_BLACK		glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)
#define zCOLOR_RED			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
#define zCOLOR_GREEN		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
#define zCOLOR_BLUE			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
#define zCOLOR_DARK_RED		glm::vec4(0.17f, 0.07f, 0.13f, 1.0f)
#define zCOLOR_DARK_GREEN	glm::vec4(0.13f, 0.17f, 0.07f, 1.0f)
#define zCOLOR_DARK_BLUE	glm::vec4(0.07f, 0.13f, 0.17f, 1.0f)

#define zE_SCREEN_COLOR(color)		glClearColor(color.x, color.y, color.z, color.w)


const unsigned int width = 800;
const unsigned int height = 800;


/** Vertices coordinates */
Vertex vertices[] = {
	/**  Coordinates     |         Colors       | Texture Coords |        Normals       */
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,   1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
};

/** Indices for vertices order */
GLuint indices[] = {
	0, 1, 2,	// Bottom side
	0, 2, 3,	// Bottom side
};

/** Light vertices coordinates */
Vertex lightVertices[] = {
	/**  Coordinates  */
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,   0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,   0.1f,  0.1f)},
};

/** Indices for light vertices order */
GLuint lightIndices[] = {
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
	4, 6, 7,
};

int main()
{
	/** Initializes the GLFW */
	glfwInit();

	/** Tell GLFW what version of OpenGL we are using */
	/** In this case we are using OpenGL 3.3 */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	/** Tell GLFW we are using the CORE profile */
	/** So that means we only have the modern functions */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/** Create a GLFWwindow object of width by height pixels, naming it "Test Window" */
	GLFWwindow* window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	/** Null check the window */
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	/** Introduce the window into the current context */
	glfwMakeContextCurrent(window);

	/** Load GLAD so it configures OpenGL */
	gladLoadGL();

	/** Specify the viewport of OpenGL in the Window */
	/** In this case, the viewport goes from x = 0, y = 0, to x = 800, y = 800 */
	glViewport(0, 0, width, height);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	/** Texture */
	Texture textures[]{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
	};

	/** Generates Shader object using shaders default.vert and default.frag */
	Shader shaderProgram("default.vert", "default.frag");
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	//Mesh floor(verts, ind, tex);
	Mesh floor(MESH_PLANE, tex);

	/** Shader for the Light object */
	Shader lightShader("light.vert", "light.frag");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
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
	Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));

	/** Main while loop */
	while (!glfwWindowShouldClose(window)) {
		/** Specify the color of the background (normalized RGB) */
		zE_SCREEN_COLOR(zCOLOR_DARK_RED);
		/** Clean the back buffer with the front buffer */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/** Handles the camera controls */
		camera.Inputs(window);
		/** Updates and exports the camera matrix to the Vertex Shader */
		camera.UpdateMatrix(60.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		/** Swap the back buffer with the front buffer */
		glfwSwapBuffers(window);

		/** Take care of all GLFW events */
		glfwPollEvents();
	}

	/** Delete all the objects we created */
	lightShader.Delete();
	shaderProgram.Delete();

	/** Delete window before ending the program */
	glfwDestroyWindow(window);
	/** Terminates the window */
	glfwTerminate();
	return 0;
}