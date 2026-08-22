#pragma once
#include "core/Node.hpp"

class MainScene : public Node {
public:
    MainScene();
    ~MainScene();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;
private:
    void processInput();
};