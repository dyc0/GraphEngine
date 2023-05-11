#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include <string>

class Application
{
	public:
	static Application* createApplication();
	virtual ~Application();
	static Application* app;
	
	virtual void init(int width, int height, const std::string title);
	virtual void startup();
	virtual void run();
	virtual void render(double currentTime);
	virtual void shutdown();

	void setWindowTitle(const std::string title);
	void getMousePosition(int& x, int& y);


	virtual void windowSizeCallback(GLFWwindow* window, int width, int height); 
	virtual void keyCallback(int key, int scancode, int action, int mods); 
	virtual void cursorPosCallback(GLFWwindow* window, double xpos, double ypos); 
	virtual void mouseButtonCallback(GLFWwindow* window,
									 int button, int action, int mods); 
	virtual void scrollCallback(GLFWwindow* window,
								double xoffset, double yoffset);

	protected:
	static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
	static void glfwKeyCallback(GLFWwindow* window,
								int key, int scancode, int action, int mods);	
	static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void glfwMouseButtonCallback(GLFWwindow* window,
		   								int button, int action, int mods);
	static void glfwScrollCallback(GLFWwindow* window,
								   double xoffset, double yoffset);	

	private:
	void strTest(std::string name) const;

	private:
	Application();

	public:
	struct APPINFO
	{
		std::string title;
		int WindowWidth;
		int WindowHeight;
		int MajorVersion;
		int MinorVersion;
		int samples;
		union
		{
			struct
			{
				unsigned int fullscreen	: 1;
				unsigned int vsync		: 1;
				unsigned int cursor		: 1;
				unsigned int stereo		: 1;
				unsigned int debug		: 1;
				unsigned int robust		: 1;
			};
			unsigned int 	 all;
		} flags;
	};

	protected:
	APPINFO info;
	GLFWwindow* window;
};

#endif
