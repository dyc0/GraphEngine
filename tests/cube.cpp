#include "application.hpp"
#include "object.hpp"
#include "shader.hpp"

class CubeApp: public Application
{
	public:
	Object* cube;
	ObjectHandler* oh;
	Shader* sh; 

	virtual void startup() override
	{
		oh = new ObjectHandler();
		
		cube = oh->loadOBJ("res/default_cube.obj");
		std::cout << "VERTICES" << std::endl;
		for (auto vertex: cube->vertices)
			std::cout << vertex.x << "," << vertex.y << "," << vertex.z << std::endl;
		std::cout << "NORMALS" << std::endl;
		for (auto normal: cube->normals)
			std::cout << normal.x << "," << normal.y << "," << normal.z << std::endl;
		std::cout << "UVS" << std::endl;
		for (auto uv: cube->uvs)
			std::cout << uv.x << "," << uv.y << std::endl;
		cube->generateBuffers();

		std::cout
			<< (cube->vertices.size() == cube->normals.size() && cube->normals.size() == cube->uvs.size())
			<< std::endl;

		sh = new Shader();
		sh->createVertexShader( "res/cube.vert");
		sh->createFragmentShader("res/cube.frag");
		sh->generateShaderProgram();

		cube->setShaderProgram(sh->getProgram());
		cube->bindShader();
	}

	virtual void render(double currentTime) override
	{
		cube->render();	
	}
};

int main()
{
	CubeApp* app = new CubeApp();
	app->run();
}
