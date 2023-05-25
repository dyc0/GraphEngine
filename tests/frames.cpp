#include "application.hpp"
#include "object.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <bits/chrono.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>
#include <cmath>
#include <cstddef>
#include <glm/trigonometric.hpp>
#include <string>
#include <fstream>

#define APP_VERT_ARRAY_SIZE 42*8

class AppVertices: public Application
{
	public:
	AppVertices()
	{
		ObjectHandler* oh = new ObjectHandler();
		cube = oh->loadOBJ("res/default_cube.obj");
		shader = new Shader();
	}

	Object* cube;
	Shader* shader;

	float vertices[APP_VERT_ARRAY_SIZE];
	float quadVertices[24];
	GLuint tex;
	GLuint vertexShader, fragmentShader, shaderProgram;
	GLint uniColor;
	GLint uniMod, uniView, uniProj;
	GLuint texColorBuffer, rboDepthStencil, frameBuffer;
	glm::mat4 model, view, proj;

	std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tNow;
	float time;

	virtual void startup() override
	{
		tStart = std::chrono::high_resolution_clock::now();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		view = glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f),
			   			   glm::vec3(0.0f, 0.0f, 0.0f),
			               glm::vec3(0.0f, 0.0f, 1.0f));

		proj = glm::perspective(glm::radians(45.0f),
			   				   (float)info.WindowWidth / (float)info.WindowHeight,
							   1.0f, 10.0f);

		cube->generateBuffers();
		cube->loadTexture("res/sample.png");

		// SCENE SHADER PROGRAMS

		shader->createVertexShader("res/fram.vert");
		shader->createFragmentShader("res/fram.frag");
		shader->generateShaderProgram();
		shaderProgram = shader->getProgram();

		cube->setShaderProgram(shader->getProgram());
		cube->bindShader();

		glUseProgram(shaderProgram);

			uniMod = glGetUniformLocation(shaderProgram, "model");
			glUniformMatrix4fv(uniMod, 1, GL_FALSE, glm::value_ptr(model));

			uniView = glGetUniformLocation(shaderProgram, "view");
			glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

			uniProj = glGetUniformLocation(shaderProgram, "proj");
			glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
	}

	
	void render(double currentTime) override
	{
		// Draw cube to framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glBindVertexArray(cube->vao);
		glEnable(GL_DEPTH_TEST);
		glUseProgram(shaderProgram);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube->texture);

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tNow = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::duration<float>>(tNow - tStart).count();

		model = glm::mat4(1.0f);
		model = glm::rotate(model, time*glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniMod, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glStencilMask(0xFF);
			glDepthMask(GL_FALSE);
			glClear(GL_STENCIL_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 36, 6);
			
			glStencilFunc(GL_EQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDepthMask(GL_TRUE);

			model = glm::scale(glm::translate(model, glm::vec3(0, 0, -1)), glm::vec3(1, 1, -1));
			glUniformMatrix4fv(uniMod, 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(uniColor, 0.3f, 0.3f, 0.3f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisable(GL_STENCIL_TEST);
	}

};

int main()
{
	AppVertices* app = new AppVertices();
	app->run();
	return 0;
}
