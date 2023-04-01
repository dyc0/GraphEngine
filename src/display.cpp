#include "display.hpp"

Display::Display(int width, int height, const std::string& title)
{
    std::cout << "Constructor!" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING); // Not good to be here if used for something else beside windows

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize." << std::endl;
    }

    m_isClosed = false;
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Display::is_closed()
{
    return m_isClosed;
}

void Display::clear(const float r, const float g, const float b, const float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Display::update()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) m_isClosed = true;
    }
}