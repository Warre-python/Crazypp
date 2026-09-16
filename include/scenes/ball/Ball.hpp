#pragma once

#include "../../nodes/Node.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class CircleCollider;

class Ball : public Node {
public:
    Ball(const glm::vec2& position, const glm::vec2& velocity,
            float radius, const glm::vec4& color,
            float gravity = 200.0f, float bounciness = 1.0f, float friction = 1.0f, float airResistance = 1.0f, float mass = 1.0f);

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;
            void resolveCollision(Ball& other);

private:
    CircleCollider* m_collider = nullptr;
    glm::vec2 m_velocity;
    float m_gravity;
    float m_bounciness;
    float m_friction;
    float m_airResistance;
    float m_mass;
};
