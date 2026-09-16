#pragma once
#include "../../nodes/Node.hpp"

class SnakeGame : public Node {
public:
    SnakeGame();
    ~SnakeGame();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

    static inline float size = 20.0f; 

    void increaseScore(int amount);


private:
    int m_score = 0;
    void processInput();
};

