#pragma once
#include "../core/Node.hpp"
#include "rendering/Renderer.hpp"
#include <glm/vec2.hpp>

class Player : public Node {
public:
    Player();
    ~Player();

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    Node* m_sprite = nullptr;
    glm::vec2 m_velocity;
};