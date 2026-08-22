#pragma once

#include "../core/Node.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class CircleCollider;

class Ball : public Node {
public:
    Ball(const glm::vec2& position, const glm::vec2& velocity,
            float radius, const glm::vec4& color,
            float gravity = 100.0f);

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    CircleCollider* m_collider = nullptr;
    glm::vec2 m_velocity;
    float m_gravity;
};
