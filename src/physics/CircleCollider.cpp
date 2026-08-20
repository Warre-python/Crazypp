#include "physics/CircleCollider.hpp"

bool CircleCollider::collideWithBorder(float windowWidth, float windowHeight,
                                       float& posX, float& posY, glm::vec2& normal) {
    bool collided = false;
    normal = glm::vec2(0.0f);

    if (posX - m_radius < 0.0f) {
        posX = m_radius;
        normal.x += 1.0f;
        collided = true;
    } else if (posX + m_radius > windowWidth) {
        posX = windowWidth - m_radius;
        normal.x -= 1.0f;
        collided = true;
    }

    if (posY - m_radius < 0.0f) {
        posY = m_radius;
        normal.y += 1.0f;
        collided = true;
    } else if (posY + m_radius > windowHeight) {
        posY = windowHeight - m_radius;
        normal.y -= 1.0f;
        collided = true;
    }

    return collided;
}