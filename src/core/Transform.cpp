#include "core/Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

Transform2D::Transform2D()
    : m_position{0.0f, 0.0f}, m_rotation(0.0f), m_scale{1.0f, 1.0f} {
}

Transform2D::~Transform2D() {
}

void Transform2D::setPosition(float x, float y) {
    m_position[0] = x;
    m_position[1] = y;
}

void Transform2D::setRotation(float angle) {
    m_rotation = angle;
}

void Transform2D::setScale(float scaleX, float scaleY) {
    m_scale[0] = scaleX;
    m_scale[1] = scaleY;
}

glm::mat4 Transform2D::getMatrix() const {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(m_position[0], m_position[1], 0.0f));
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale[0], m_scale[1], 1.0f));

    return translation * rotation * scale;
}
