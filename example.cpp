#include "graph_engine.hpp"
#include "mesh.hpp"

int main()
{
    Display disp(800, 600, "First");
     
    Vertex vertices[] = {
		       	Vertex(glm::vec3(-0.5, -0.5, 0)),
	    	       	Vertex(glm::vec3(0, 0.5, 0)),
		       	Vertex(glm::vec3(0.5, -0.5, 0))
		      	};

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

    Shader shader("./res/basicShader");

    while (!disp.is_closed())
    {
        disp.clear(1, 1, 1, 1);

        shader.bind();
	mesh.draw();

        disp.update();
    }

    return 0;
}
