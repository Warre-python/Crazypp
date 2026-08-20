#include "Game.hpp"
#include <iostream>
#include "Window.hpp"
#include "Shader.hpp"

Game::Game()
    : m_window(800, 600, "OpenGL Game"),
      m_shader("res/shaders/basic.glsl"),
      m_running(true) {
}

Game::~Game() {
    
}

void Game::run() {
    m_shader.compile();
    m_shader.use();
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
    m_window.swapBuffers();
    m_window.pollEvents();

}