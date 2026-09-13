#include "scenes/GameManager.hpp"

GameManager::GameManager() {
    auto game = std::make_unique<SnakeGame>();
    m_game = game.get();
    addChild(std::move(game));
}

GameManager::~GameManager() {
    // Destructor implementation
}

void GameManager::update(float deltaTime) {
    processInput();
    for (const auto& child : m_children) {
        child->update(deltaTime);
    }

    if (m_resetRequested) {
        resetGame();
    }
}

void GameManager::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}

void GameManager::requestReset() {
    m_resetRequested = true;
}

void GameManager::resetGame() {
    m_game = nullptr;
    m_resetRequested = false;
    m_children.clear();

    auto game = std::make_unique<SnakeGame>();
    m_game = game.get();
    addChild(std::move(game));
}

void GameManager::processInput() {
    // Handle input for the game manager (if any)
}

