#include "Game.hpp"
#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"
#include "rendering/Renderer.hpp"

Game::Game()
    : m_window(800, 600, "Crazy++"),
      m_renderer(),
      m_running(true) {
}

Game::~Game() {
    
}

void Game::run() {
    while (m_running && !m_window.shouldClose()) {
        processInput();
        update();
        render();
    }
}

void Game::processInput() {
    m_window.processInput();
}

void Game::update() {
    m_window.clear(1.0f, 0.1f, 0.1f, 1.0f);

}

void Game::render() {
    m_renderer.render();
    m_window.swapBuffers();
    m_window.pollEvents();

}