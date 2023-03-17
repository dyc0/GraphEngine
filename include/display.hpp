#ifndef display_h
#define display_h

#include "externals.hpp"

class Display
{
    public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void clear(const float r, const float g, const float b, const float a);
    void update();
    bool is_closed();

    protected:
    private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif
