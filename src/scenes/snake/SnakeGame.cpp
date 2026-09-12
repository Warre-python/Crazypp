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
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}

void SnakeGame::processInput() {
    
}