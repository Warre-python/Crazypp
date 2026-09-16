#include "nodes/Sprite.hpp"
#include "nodes/Texture.hpp"
#include "rendering/Renderer.hpp"
#include <cmath>

Sprite::Sprite() {
    m_transform.setPosition(0.0f, 0.0f);
    rectangle(100.0f, 100.0f);
}

void Sprite::draw(Renderer& renderer) {
    if (m_vertices.empty() || m_indices.empty()) {
        return;
    }

    if (m_texture != nullptr) {
        renderer.renderTexture(
            m_textureVertices.data(), static_cast<int>(m_textureVertices.size()),
            m_indices.data(), static_cast<int>(m_indices.size()),
            getWorldMatrix(), *m_texture);
    } else {
        renderer.render(
            m_vertices.data(), static_cast<int>(m_vertices.size()),
            m_indices.data(), static_cast<int>(m_indices.size()),
            getWorldMatrix(), m_color);
    }
}

void Sprite::rectangle(float width, float height) {
    const float halfWidth = width * 0.5f;
    const float halfHeight = height * 0.5f;

    m_vertices = {
        halfWidth, halfHeight, 0.0f,
        halfWidth, -halfHeight, 0.0f,
        -halfWidth, -halfHeight, 0.0f,
        -halfWidth, halfHeight, 0.0f
    };
    m_textureVertices = {
        halfWidth, halfHeight, 0.0f, 1.0f, 0.0f,
        halfWidth, -halfHeight, 0.0f, 1.0f, 1.0f,
        -halfWidth, -halfHeight, 0.0f, 0.0f, 1.0f,
        -halfWidth, halfHeight, 0.0f, 0.0f, 0.0f
    };
    m_indices = {0, 1, 3, 1, 2, 3};
}

void Sprite::circle(float radius) {
    constexpr int segments = 32;
    constexpr float pi = 3.14159265358979323846f;

    m_vertices.clear();
    m_textureVertices.clear();
    m_indices.clear();
    m_vertices.reserve((segments + 1) * 3);
    m_indices.reserve(segments * 3);

    m_vertices.insert(m_vertices.end(), {0.0f, 0.0f, 0.0f});
    for (int i = 0; i < segments; ++i) {
        const float angle = 2.0f * pi * static_cast<float>(i) / segments;
        m_vertices.push_back(radius * std::cos(angle));
        m_vertices.push_back(radius * std::sin(angle));
        m_vertices.push_back(0.0f);
    }

    for (int i = 0; i < segments; ++i) {
        const unsigned int current = static_cast<unsigned int>(i + 1);
        const unsigned int next = static_cast<unsigned int>((i + 1) % segments + 1);
        m_indices.insert(m_indices.end(), {0, current, next});
    }
}

void Sprite::setColor(float r, float g, float b, float a) {
    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
    m_color[3] = a;
}

void Sprite::setTexture(const Texture* texture) {
    m_texture = texture;
}