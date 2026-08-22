#include "scenes/MainScene.hpp"
#include "core/Node.hpp"
#include "scenes/Ball.hpp"

MainScene::MainScene() {
    addChild(std::make_unique<Ball>(
            glm::vec2(180.0f, 150.0f), glm::vec2(220.0f, 160.0f),
            35.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    addChild(std::make_unique<Ball>(
        glm::vec2(500.0f, 220.0f), glm::vec2(-180.0f, 240.0f),
        45.0f, glm::vec4(1.0f, 0.8f, 0.0f, 1.0f)));
    addChild(std::make_unique<Ball>(
        glm::vec2(350.0f, 450.0f), glm::vec2(260.0f, -190.0f),
        25.0f, glm::vec4(0.2f, 0.6f, 1.0f, 1.0f)));
}

MainScene::~MainScene() {
}

void MainScene::update(float deltaTime) {
    processInput();
    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}

void MainScene::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}

void MainScene::processInput() {
    // Process input for the main scene if needed
}