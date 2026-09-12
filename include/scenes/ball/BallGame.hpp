#pragma once
#include "core/Node.hpp"

class BallGame : public Node {
public:
    BallGame();
    ~BallGame();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;
private:
    void processInput();
};