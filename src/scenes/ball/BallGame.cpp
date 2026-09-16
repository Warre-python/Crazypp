#include "scenes/ball/BallGame.hpp"
#include "nodes/Node.hpp"
#include "scenes/ball/Ball.hpp"

BallGame::BallGame() {

    for (int i = 0; i < 5; ++i) {
        float radius = 20.0f + static_cast<float>(rand() % 30);
        glm::vec2 position(static_cast<float>(rand() % 700 + 50),
                           static_cast<float>(rand() % 100 + 50));
        glm::vec2 velocity(static_cast<float>(rand() % 400 - 200),
                           static_cast<float>(rand() % 400 - 200));
        glm::vec4 color(static_cast<float>(rand() % 100) / 100.0f,
                        static_cast<float>(rand() % 100) / 100.0f,
                        static_cast<float>(rand() % 100) / 100.0f, 1.0f);
        addChild(std::make_unique<Ball>(position, velocity, radius, color));
    }
}

BallGame::~BallGame() {
}

void BallGame::update(float deltaTime) {
    processInput();
    for (const auto& child : m_children) {
        child->update(deltaTime);
    }

    for (std::size_t first = 0; first < m_children.size(); ++first) {
        auto* firstBall = dynamic_cast<Ball*>(m_children[first].get());
        if (!firstBall) {
            continue;
        }

        for (std::size_t second = first + 1; second < m_children.size(); ++second) {
            auto* secondBall = dynamic_cast<Ball*>(m_children[second].get());
            if (secondBall) {
                firstBall->resolveCollision(*secondBall);
            }
        }
    }
}

void BallGame::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}

void BallGame::processInput() {
    // Process input for the ball game   if needed
}