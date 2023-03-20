#include "graph_engine.hpp"

int main()
{
    Display disp(800, 600, "First");
     
    Vertex vertices[] = {
		       	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
	    	    Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1)),
		       	Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0))
		      	};

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");

    while (!disp.is_closed())
    {
        disp.clear(1, 1, 1, 1);

        shader.bind();
		texture.Bind(0);
		mesh.draw();

        disp.update();
    }

    return 0;
}
