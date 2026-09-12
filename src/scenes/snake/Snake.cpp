#include "scenes/snake/Snake.hpp"
#include "rendering/Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <Input.hpp>
#include <GLFW/glfw3.h>

Snake::Snake() {
    m_bodySegments.push_back(glm::vec2(100, 100)); 
    m_bodySegments.push_back(glm::vec2(120, 100));
    m_bodySegments.push_back(glm::vec2(140, 100)); 

    

}

Snake::~Snake() {
    // Destructor implementation
}

void Snake::update(float deltaTime) {
    timer += deltaTime;
    if (timer >= 0.5f) {
        m_bodySegments.insert(m_bodySegments.begin(), m_bodySegments.front() + m_direction * static_cast<float>(m_segmentSize));
        m_bodySegments.pop_back();
        timer = 0.0f; // Reset the timer after moving the snake
    }
    
    processInput();
}

void Snake::draw(Renderer& renderer) {
    const float halfSize = m_segmentSize * 0.5f;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    vertices.reserve(m_bodySegments.size() * 12);
    indices.reserve(m_bodySegments.size() * 6);

    for (const auto& segment : m_bodySegments) {
        const unsigned int firstVertex = static_cast<unsigned int>(vertices.size() / 3);
        vertices.insert(vertices.end(), {
            segment.x - halfSize, segment.y - halfSize, 0.0f,
            segment.x + halfSize, segment.y - halfSize, 0.0f,
            segment.x + halfSize, segment.y + halfSize, 0.0f,
            segment.x - halfSize, segment.y + halfSize, 0.0f
        });
        indices.insert(indices.end(), {
            firstVertex, firstVertex + 1, firstVertex + 2,
            firstVertex, firstVertex + 2, firstVertex + 3
        });
    }

    if (vertices.empty()) {
        return;
    }

    const float color[] = {0.0f, 1.0f, 0.0f, 1.0f};
    renderer.render(
        vertices.data(), static_cast<int>(vertices.size()),
        indices.data(), static_cast<int>(indices.size()),
        getWorldMatrix(), color
    );
}

void Snake::processInput() {
    if (Input::isKeyPressed(GLFW_KEY_UP)) {
        m_direction = glm::vec2(0, -1); // Move the snake up
    } else if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
        m_direction = glm::vec2(0, 1); // Move the snake down
    } else if (Input::isKeyPressed(GLFW_KEY_LEFT)) {
        m_direction = glm::vec2(-1, 0); // Move the snake left
    } else if (Input::isKeyPressed(GLFW_KEY_RIGHT)) {
        m_direction = glm::vec2(1, 0); // Move the snake right
    }
}