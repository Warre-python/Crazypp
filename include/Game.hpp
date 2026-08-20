#pragma once
#include "Window.hpp"
#include "Shader.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    Window m_window;
    Shader m_shader;
    void processInput();
    void update();
    void render();

    bool m_running;
};