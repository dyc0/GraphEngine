#include "graph_engine.hpp"

int main()
{
    Display disp(800, 600, "First");

    Shader shader("./res/basicShader");

    while (!disp.is_closed())
    {
        disp.clear(1, 1, 1, 1);
        shader.bind();

        disp.update();
    }

    return 0;
}