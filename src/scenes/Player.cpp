#include "scenes/Player.hpp"
#include "rendering/Renderer.hpp"
#include "core/Sprite.hpp"
#include "physics/CircleCollider.hpp"
#include <glad/glad.h>
#include <glm/geometric.hpp>
#include "Input.hpp"
#include <GLFW/glfw3.h>

Player::Player() {
    m_transform.setPosition(400.0f, 300.0f);
    m_velocity = glm::vec2(220.0f, 160.0f);
    auto sprite = std::make_unique<Sprite>();
    m_sprite = sprite.get();
    sprite->circle(50.0f);
    sprite->setColor(0.0f, 1.0f, 0.0f, 1.0f);
    addChild(std::move(sprite));

    auto collider = std::make_unique<CircleCollider>(50.0f);
    addChild(std::move(collider));
    
}

Player::~Player() {
}

void Player::update(float deltaTime) {

    if (Input::isKeyPressed(GLFW_KEY_LEFT)) {
        m_velocity.x = -std::abs(m_velocity.x);
    } else if (Input::isKeyPressed(GLFW_KEY_RIGHT)) {
        m_velocity.x = std::abs(m_velocity.x);
    } else if (Input::isKeyPressed(GLFW_KEY_UP)) {
        m_velocity.y = -std::abs(m_velocity.y);
    } else if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
        m_velocity.y = std::abs(m_velocity.y);
    }

    move(m_velocity.x * deltaTime, m_velocity.y * deltaTime);

    auto collider = dynamic_cast<CircleCollider*>(m_children.back().get());
    if (collider) {
        float posX = m_transform.getPositionX();
        float posY = m_transform.getPositionY();
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        const float windowWidth = static_cast<float>(viewport[2]);
        const float windowHeight = static_cast<float>(viewport[3]);
        glm::vec2 normal(0.0f);
        if (windowWidth > 0.0f && windowHeight > 0.0f &&
            collider->collideWithBorder(windowWidth, windowHeight, posX, posY, normal)) {
            normal = glm::normalize(normal);
            m_velocity -= 2.0f * glm::dot(m_velocity, normal) * normal;
        }
        m_transform.setPosition(posX, posY);
    }
    

    for (const auto& child : m_children) {
        child->update(deltaTime);
    }
}


void Player::draw(Renderer& renderer) {
    for (const auto& child : m_children) {
        child->draw(renderer);
    }
}

