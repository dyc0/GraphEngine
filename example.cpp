#include "graph_engine.hpp"

int main()
{
    Display disp(800, 600, "First");
     
    Vertex vertices[] = {
		       	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
	    	    Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1)),
		       	Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0))
		      	};
	
	unsigned int indices[] = { 0, 1, 2 };

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Camera camera(glm::vec3(0,0,-3), 70.0f, (float)800/(float)600, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;
    while (!disp.is_closed())
    {
        disp.clear(1, 1, 1, 1);

		transform.GetPos().x = sinf(counter);
		transform.GetPos().z = cosf(counter);
		transform.GetRot().z = counter;
		transform.GetRot().y = counter;
		transform.GetRot().x = counter;
		//transform.SetScale(glm::vec3(cosf(counter), cosf(counter), cosf(counter)));

        shader.bind();
		texture.Bind(0);
		shader.update(transform, camera);
		mesh.draw();

        disp.update();
    	counter += 0.005f;
	}

    return 0;
}
