#include "core/Transform.hpp"

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
