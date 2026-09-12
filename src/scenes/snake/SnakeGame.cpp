#include "scenes/snake/SnakeGame.hpp"
#include "scenes/snake/Snake.hpp"

SnakeGame::SnakeGame() {
    addChild(std::make_unique<Snake>()); 
}

SnakeGame::~SnakeGame() {
    // Destructor implementation
}

void SnakeGame::update(float deltaTime) {
    processInput();
    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}

void SnakeGame::draw(Renderer& renderer) {
    // Drawing logic for the SnakeGame
}

void SnakeGame::processInput() {
    // Input processing logic for the SnakeGame
}