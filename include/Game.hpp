#pragma once
#include "Window.hpp"
#include "Shader.hpp"
#include "rendering/Renderer.hpp"
#include "nodes/Node.hpp"

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    Window m_window;
    Renderer m_renderer;
    std::vector<std::unique_ptr<Node>> m_nodes;

    void processInput();
    void update(float deltaTime);
    void render();
    void addNode(std::unique_ptr<Node> node);

    bool m_running;
};