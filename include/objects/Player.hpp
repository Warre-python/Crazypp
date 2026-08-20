#pragma once
#include "../core/Node.hpp"

class Player : public Node {
public:
    Player();
    ~Player();

    void update(float deltaTime) override;
    void draw() override;

};