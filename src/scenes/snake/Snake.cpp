#include "scenes/snake/Snake.hpp"
#include "rendering/Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <Input.hpp>
#include <GLFW/glfw3.h>

Snake::Snake() {
    m_bodySegments.push_back(glm::vec2(5, 5)); //
    
}

Snake::~Snake() {
    // Destructor implementation
}

void Snake::update(float deltaTime) {
    if (m_bodySegments.empty()) {
        return; // No segments to update
    }
    processInput();
}

void Snake::draw(Renderer& renderer) {
    for (const auto& segment : m_bodySegments) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(segment, 0.0f));
        float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Green color for the snake segments
        renderer.render(nullptr, 0, nullptr, 0, model, color);
    }
}

void Snake::processInput() {
    if (Input::isKeyPressed(GLFW_KEY_UP)) {
        m_direction = glm::vec2(0, 1); // Move the snake up
    } else if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
        m_direction = glm::vec2(0, -1); // Move the snake down
    } else if (Input::isKeyPressed(GLFW_KEY_LEFT)) {
        m_direction = glm::vec2(-1, 0); // Move the snake left
    } else if (Input::isKeyPressed(GLFW_KEY_RIGHT)) {
        m_direction = glm::vec2(1, 0); // Move the snake right
    }
}