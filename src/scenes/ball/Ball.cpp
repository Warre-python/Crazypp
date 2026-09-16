#include "scenes/ball/Ball.hpp"
#include "nodes/Sprite.hpp"
#include "physics/CircleCollider.hpp"
#include <glad/glad.h>
#include <glm/geometric.hpp>
#include <algorithm>
#include <cmath>

Ball::Ball(const glm::vec2& position, const glm::vec2& velocity,
                float radius, const glm::vec4& color, float gravity, float bounciness,
                float friction, float airResistance, float mass)
        : m_velocity(velocity),
            m_gravity(gravity),
            m_bounciness(bounciness),
            m_friction(friction),
            m_airResistance(airResistance),
            m_mass(std::max(mass, 0.0001f)) {
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
    const float frameScale = deltaTime * 60.0f;
    m_velocity.y += (m_gravity / m_mass) * deltaTime;
    m_velocity *= std::pow(std::clamp(m_airResistance, 0.0f, 1.0f), frameScale);
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
            m_velocity -= (1.0f + m_bounciness)
                * glm::dot(m_velocity, normal) * normal;

            const glm::vec2 normalVelocity = glm::dot(m_velocity, normal) * normal;
            const glm::vec2 tangentVelocity = m_velocity - normalVelocity;
            m_velocity = normalVelocity
                + tangentVelocity * std::clamp(m_friction, 0.0f, 1.0f);
        }

        m_transform.setPosition(positionX, positionY);
    }

    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}

void Ball::resolveCollision(Ball& other) {
    const glm::vec2 position(
        m_transform.getPositionX(), m_transform.getPositionY());
    const glm::vec2 otherPosition(
        other.m_transform.getPositionX(), other.m_transform.getPositionY());
    const glm::vec2 difference = otherPosition - position;
    const float minimumDistance = m_collider->getRadius()
        + other.m_collider->getRadius();
    const float distanceSquared = glm::dot(difference, difference);

    if (distanceSquared >= minimumDistance * minimumDistance) {
        return;
    }

    const float distance = std::sqrt(distanceSquared);
    const glm::vec2 normal = distance > 0.0001f
        ? difference / distance
        : glm::vec2(1.0f, 0.0f);
    const float overlap = minimumDistance - distance;
    const float inverseMass = 1.0f / m_mass;
    const float otherInverseMass = 1.0f / other.m_mass;
    const float inverseMassTotal = inverseMass + otherInverseMass;

    m_transform.setPosition(
        position.x - normal.x * overlap * inverseMass / inverseMassTotal,
        position.y - normal.y * overlap * inverseMass / inverseMassTotal);
    other.m_transform.setPosition(
        otherPosition.x + normal.x * overlap * otherInverseMass / inverseMassTotal,
        otherPosition.y + normal.y * overlap * otherInverseMass / inverseMassTotal);

    const glm::vec2 relativeVelocity = other.m_velocity - m_velocity;
    const float velocityAlongNormal = glm::dot(relativeVelocity, normal);
    if (velocityAlongNormal >= 0.0f) {
        return;
    }

    const float restitution = std::min(m_bounciness, other.m_bounciness);
    const float impulseMagnitude = -(1.0f + restitution)
        * velocityAlongNormal / inverseMassTotal;
    const glm::vec2 impulse = impulseMagnitude * normal;
    m_velocity -= inverseMass * impulse;
    other.m_velocity += otherInverseMass * impulse;

    const glm::vec2 tangent(
        -normal.y, normal.x);
    const float tangentSpeed = glm::dot(other.m_velocity - m_velocity, tangent);
    const float friction = std::sqrt(std::clamp(m_friction, 0.0f, 1.0f)
        * std::clamp(other.m_friction, 0.0f, 1.0f));
    const glm::vec2 frictionImpulse = tangentSpeed * friction / inverseMassTotal
        * tangent;
    m_velocity += inverseMass * frictionImpulse;
    other.m_velocity -= otherInverseMass * frictionImpulse;
}

void Ball::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}
