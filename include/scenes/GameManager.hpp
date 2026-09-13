#pragma once
#include "../core/Node.hpp"
#include "snake/SnakeGame.hpp"

class GameManager : public Node {
public:
    GameManager();
    ~GameManager();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

    void requestReset();
    void resetGame();

private:
    SnakeGame* m_game = nullptr;
    bool m_resetRequested = false;

    void processInput();
};