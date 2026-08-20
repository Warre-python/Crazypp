#pragma once
#include "Window.hpp"
#include "Shader.hpp"
#include "rendering/Renderer.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    Window m_window;
    Renderer m_renderer;

    void processInput();
    void update();
    void render();

    bool m_running;
};