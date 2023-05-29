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

class AppVertices: public Application
{
	public:
	AppVertices()
	{
		ObjectHandler* oh = new ObjectHandler();
		cube = oh->loadOBJ("res/teapot_triang.obj");
		shader = new Shader();
	}

	Object* cube;
	Shader* shader;

	GLuint shaderProgram;
	GLint uniMod, uniView, uniProj;
	GLuint texColorBuffer, rboDepthStencil, frameBuffer;

	std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tNow;
	float time;

	virtual void startup() override
	{
		tStart = std::chrono::high_resolution_clock::now();

		cube->generateBuffers();
		cube->loadTexture("res/porcelain.jpg");

		shader->createVertexShader("res/fram.vert");
		shader->createFragmentShader("res/fram.frag");
		shader->generateShaderProgram();
		shaderProgram = shader->getProgram();

		shader->setCamera(glm::lookAt(glm::vec3(2.5f, 2.5f, 2.5f),
			   			  glm::vec3(0.0f, 0.0f, 0.0f),
			              glm::vec3(0.0f, 0.0f, 1.0f)));
		shader->setPerspective(glm::perspective(glm::radians(45.0f),
			   				   (float)info.WindowWidth / (float)info.WindowHeight,
							   1.0f, 10.0f));
		shader->bindGlobalTransforms();

		cube->setShaderProgram(shader->getProgram());
		cube->bindShader();
	}

	
	void render(double currentTime) override
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(cube->vao);
		glUseProgram(shaderProgram);
		
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		tNow = std::chrono::high_resolution_clock::now();
		time = std::chrono::duration_cast<std::chrono::duration<float>>(tNow - tStart).count();

		cube->setTransform(glm::rotate(glm::mat4(1.0f), time*glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

		cube->render();
	}

};

int main()
{
	AppVertices* app = new AppVertices();
	app->run();
	return 0;
}
