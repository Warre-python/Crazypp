#pragma once
#include "../../core/Node.hpp"

class SnakeGame : public Node {
public:
    SnakeGame();
    ~SnakeGame();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    void processInput();
};