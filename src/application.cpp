#include "application.hpp"

Application* Application::createApplication()
{
	if (!app)
		app = new Application();
	return app;
}

Application::Application()
{
		info.MajorVersion = 3;
		info.MinorVersion = 2;
		info.title = "OpenGL";
		info.WindowWidth = 1280;
		info.WindowHeight = 720;
		info.flags.all = false;
		info.flags.debug = true;
		app = this;
}

Application::~Application() { };

void Application::init(int width, int height, std::string title)
{
	info.WindowWidth = width;
	info.WindowHeight = height;
	info.title = title;
}

void Application::startup() { }

void Application::run()
{ 
	if (!glfwInit())
	{
		// TODO: Set up exception here.
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (info.flags.debug)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	if (info.flags.robust)
		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
	
	glfwWindowHint(GLFW_SAMPLES, info.samples);
	glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);

	window = glfwCreateWindow(
			 info.WindowWidth, 
			 info.WindowHeight, 
			 info.title.c_str(), 
			 nullptr, nullptr);
	if (!window)
	{
		//TODO: Exception handling.
		return;
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
	glfwSetCursorPosCallback(window, glfwCursorPosCallback);
	glfwSetScrollCallback(window, glfwScrollCallback);

	glewInit();
	startup();
	while(!glfwWindowShouldClose(window))
	{
		render(glfwGetTime());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shutdown();
	glfwDestroyWindow(window);

	glfwTerminate();
}

void Application::render(double currentTime) { }

void Application::shutdown() { }


void Application::windowSizeCallback(GLFWwindow* window, int width, int height) { strTest("Size"); }
void Application::keyCallback(int key, int scancode, int action, int mods) { strTest("Keypress"); }
void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) { strTest("Cursor"); }
void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { strTest("Click"); }
void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) { strTest("Scroll"); }


void Application::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{ app->windowSizeCallback(window, width, height); }

void Application::glfwKeyCallback(GLFWwindow* window,
								  int key, int scancode, int action, int mods)
{ app->keyCallback(key, scancode, action, mods); }

void Application::glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{ app->cursorPosCallback(window, xpos, ypos); }

void Application::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{ app->mouseButtonCallback(window, button, action, mods); }

void Application::glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{ app->scrollCallback(window, xoffset, yoffset); }


void Application::strTest(std::string name) const
{ if(info.flags.debug) std::cout << name << std::endl; }

Application* Application::app = nullptr;
