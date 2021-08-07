#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "ShaderClass.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

/** Vertices coordinates */
GLfloat vertices[] = {
	/**  Coordinates     |         Colors           | Texture Coords |        Normals       */
	-0.5f, 0.0f,  0.5f,		0.83f, 0.70f,  0.44f,		0.0f,  0.0f,	0.0f, -1.0f,  0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		0.0f,  5.0f, 	0.0f, -1.0f,  0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		5.0f,  5.0f, 	0.0f, -1.0f,  0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,		0.83f, 0.70f,  0.44f,		5.0f,  0.0f, 	0.0f, -1.0f,  0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,		0.83f, 0.70f,  0.44f,		0.0f,  0.0f,   -0.8f,  0.5f,  0.0f, // Left side
	-0.5f, 0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		5.0f,  0.0f,   -0.8f,  0.5f,  0.0f, // Left side
	 0.0f, 0.8f,  0.0f,		0.92f, 0.86f,  0.76f,		2.5f,  5.0f,   -0.8f,  0.5f,  0.0f, // Left side

	-0.5f, 0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		5.0f,  0.0f,    0.0f,  0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		0.0f,  0.0f,    0.0f,  0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,		0.92f, 0.86f,  0.76f,		2.5f,  5.0f,    0.0f,  0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,		0.83f, 0.70f,  0.44f,		0.0f,  0.0f,    0.8f,  0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,		0.83f, 0.70f,  0.44f,		5.0f,  0.0f,    0.8f,  0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,		0.92f, 0.86f,  0.76f,		2.5f,  5.0f,    0.8f,  0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,		0.92f, 0.86f,  0.76f,		5.0f,  0.0f,    0.0f,  0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,		0.92f, 0.86f,  0.76f,		0.0f,  0.0f,    0.0f,  0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,		0.92f, 0.86f,  0.76f,		2.5f,  5.0f,    0.0f,  0.5f,  0.8f, // Facing side

};

/** Indices for vertices order */
GLuint indices[] = {
	0, 1, 2,	// Bottom side
	0, 2, 3,	// Bottom side
	4, 6, 5,	// Left side
	7, 9, 8,	// Non-facing side
	10, 12, 11,	// Right side
	13, 15, 14,	// Facing side
};

/** Light vertices coordinates */
GLfloat lightVertices[] = {
	/**  Coordinates  */
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
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

	/** Create a GLFWwindow object of 800 by 800 pixels, naming it "Test Window" */
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
	
	Shader shaderProgram("default.vert", "default.frag");

	VertexArrayObject vao;
	vao.Bind();

	/** Generates Vertex Buffer Object and links it to vertices */
	VertexBufferObject vbo(vertices, sizeof(vertices));
	/** Generates Element Buffer Object and links it to indices */
	ElementBufferObject ebo(indices, sizeof(indices));

	/** Links vbo to vao */
	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.LinkAttrib(vbo, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	/** Unbind all to prevent accidentally modifying them */
	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();


	Shader lightShader("light.vert", "light.frag");

	VertexArrayObject lightVAO;
	lightVAO.Bind();

	VertexBufferObject lightVBO(lightVertices, sizeof(lightVertices));
	ElementBufferObject lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	/** Texture */
	Texture texture("gollum.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.TexUnit(shaderProgram, "tex0", 0);

	/** Enables the depth buffer */
	glEnable(GL_DEPTH_TEST);

	/** Create camera object */
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	/** Main while loop */
	while (!glfwWindowShouldClose(window)) {
		/** Specify the color of the background (normalized RGB) */
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		/** Clean the back buffer with the front buffer */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/** Handles the camera controls */
		camera.Inputs(window);
		/** Updates and exports the camera matrix to the Vertex Shader */
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		/** Tell OpenGL which Shader Program we want to use */
		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");

		texture.Bind();
		/** Bind the Vertex Array Object so OpenGL knows to use it */
		vao.Bind();
		/** Draw the primitives, number of indices, data type of indices, index of indices */
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		/** Swap the back buffer with the front buffer */
		glfwSwapBuffers(window);

		/** Take care of all GLFW events */
		glfwPollEvents();
	}

	/** Delete all the objects we created */
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	texture.Delete();
	shaderProgram.Delete();

	/** Delete window before ending the program */
	glfwDestroyWindow(window);
	/** Terminates the window */
	glfwTerminate();
	return 0;
}