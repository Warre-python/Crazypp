#include "Game.hpp"
#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"
#include "rendering/Renderer.hpp"
#include "nodes/Node.hpp"
#include "scenes/GameManager.hpp"
#include "scenes/ball/BallGame.hpp"

Game::Game()
    : m_window(800, 600, "Crazy++"),
      m_renderer(),
      m_running(true) {

    addNode(std::make_unique<GameManager>());
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
    m_window.clear(0.1f, 0.1f, 0.1f, 1.0f);



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