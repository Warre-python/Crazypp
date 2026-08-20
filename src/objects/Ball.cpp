#include "objects/Ball.hpp"
#include "core/Sprite.hpp"
#include "physics/CircleCollider.hpp"
#include <glad/glad.h>
#include <glm/geometric.hpp>

Ball::Ball(const glm::vec2& position, const glm::vec2& velocity,
        float radius, const glm::vec4& color, float gravity)
    : m_velocity(velocity), m_gravity(gravity) {
    m_transform.setPosition(position.x, position.y);

    auto sprite = std::make_unique<Sprite>();
    sprite->circle(radius);
    sprite->setColor(color.r, color.g, color.b, color.a);
    addChild(std::move(sprite));

    auto collider = std::make_unique<CircleCollider>(radius);
    m_collider = collider.get();
    addChild(std::move(collider));
}

void Ball::update(float deltaTime) {
    m_velocity.y += m_gravity * deltaTime;
    move(m_velocity.x * deltaTime, m_velocity.y * deltaTime);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    const float windowWidth = static_cast<float>(viewport[2]);
    const float windowHeight = static_cast<float>(viewport[3]);

    if (m_collider && windowWidth > 0.0f && windowHeight > 0.0f) {
        float positionX = m_transform.getPositionX();
        float positionY = m_transform.getPositionY();
        glm::vec2 normal(0.0f);

        if (m_collider->collideWithBorder(
                windowWidth, windowHeight, positionX, positionY, normal)) {
            normal = glm::normalize(normal);
            m_velocity -= 2.0f * glm::dot(m_velocity, normal) * normal;
        }

        m_transform.setPosition(positionX, positionY);
    }

    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}

void Ball::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}
