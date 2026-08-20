#include "Game.hpp"
#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"
#include "rendering/Renderer.hpp"
#include "objects/Ball.hpp"
#include "core/Node.hpp"

Game::Game()
    : m_window(800, 600, "Crazy++"),
      m_renderer(),
      m_running(true) {

        addNode(std::make_unique<Ball>(
            glm::vec2(180.0f, 150.0f), glm::vec2(220.0f, 160.0f),
            35.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
        addNode(std::make_unique<Ball>(
            glm::vec2(500.0f, 220.0f), glm::vec2(-180.0f, 240.0f),
            45.0f, glm::vec4(1.0f, 0.8f, 0.0f, 1.0f)));
        addNode(std::make_unique<Ball>(
            glm::vec2(350.0f, 450.0f), glm::vec2(260.0f, -190.0f),
            25.0f, glm::vec4(0.2f, 0.6f, 1.0f, 1.0f)));
}

Game::~Game() {
    
}

void Game::run() {
    while (m_running && !m_window.shouldClose()) {
        const float deltaTime = m_window.getDeltaTime();
        processInput();
        update(deltaTime);
        render();
    }
}

void Game::processInput() {
    m_window.processInput();
}

void Game::update(float deltaTime) {
    for (const auto& node : m_nodes) {
        node->update(deltaTime);
    }
}

void Game::render() {
    m_window.clear(1.0f, 0.1f, 0.1f, 1.0f);



    for (const auto& node : m_nodes) {
        node->draw(m_renderer);
    }



    m_window.swapBuffers();
    m_window.pollEvents();

}

void Game::addNode(std::unique_ptr<Node> node) {
    if (!node) {
        return;
    }
    m_nodes.push_back(std::move(node));
}