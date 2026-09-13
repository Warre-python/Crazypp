#include "scenes/snake/Snake.hpp"
#include "rendering/Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <Input.hpp>
#include <GLFW/glfw3.h>
#include "scenes/snake/SnakeGame.hpp"
#include "scenes/snake/Apple.hpp"

Snake::Snake() {
    int initialSegments = 5; // Number of initial segments
    
    for (int i = 0; i < initialSegments-1; ++i) {
        m_bodySegments.push_back(m_bodySegments.back() - m_direction * SnakeGame::size);
    }

    

}

Snake::~Snake() {
    // Destructor implementation
}

void Snake::update(float deltaTime) {
    timer += deltaTime;
    if (timer >= 0.2f) {
        m_bodySegments.insert(m_bodySegments.begin(), m_bodySegments.front() + m_direction * SnakeGame::size);
        m_bodySegments.pop_back();
        timer = 0.0f; // Reset the timer after moving the snake
    }

    if (m_bodySegments.size() > 1) {
        for (size_t i = 1; i < m_bodySegments.size(); ++i) {
            if (m_bodySegments[0] == m_bodySegments[i]) {
                // Handle collision with itself (e.g., reset the game or end it)
                m_bodySegments.resize(3); // Reset to just the head
                break;
            }
        }
    }

    if (m_parent) {
        if (auto apple = m_parent->getChild<Apple>()) {
            if (m_bodySegments[0] == apple->getPosition()) {
            m_bodySegments.push_back(m_bodySegments.back()); // Add a new segment at the tail
                apple->setPosition((rand() % 20) * SnakeGame::size, (rand() % 20) * SnakeGame::size); // Move the apple to a new random position
            }
        }
    }

    processInput();
}

void Snake::draw(Renderer& renderer) {
    const float halfSize = SnakeGame::size * 0.5f;
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
        if (m_direction != glm::vec2(0, 1)){
            // Prevent reversing direction
            m_direction = glm::vec2(0, -1); // Move the snake up
        } 
    } else if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
        if (m_direction != glm::vec2(0, -1)){
            // Prevent reversing direction
            m_direction = glm::vec2(0, 1); // Move the snake down
        }
    } else if (Input::isKeyPressed(GLFW_KEY_LEFT)) {
        if (m_direction != glm::vec2(1, 0)){
            // Prevent reversing direction
            m_direction = glm::vec2(-1, 0); // Move the snake left
        }  
    } else if (Input::isKeyPressed(GLFW_KEY_RIGHT)) {
        if (m_direction != glm::vec2(-1, 0)){
            // Prevent reversing direction
            m_direction = glm::vec2(1, 0); // Move the snake right
        }
    }
}