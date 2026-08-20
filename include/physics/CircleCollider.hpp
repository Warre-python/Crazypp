#pragma once
#include "core/Node.hpp"
#include <glm/vec2.hpp>

class CircleCollider : public Node {
public:
    CircleCollider(float radius) : m_radius(radius) {}

    float getRadius() const { return m_radius; }
    void setRadius(float radius) { m_radius = radius; }

    bool collideWithBorder(float windowWidth, float windowHeight,
                           float& posX, float& posY, glm::vec2& normal);

private:
    float m_radius;
};