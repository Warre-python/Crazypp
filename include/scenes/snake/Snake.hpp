#pragma once

#include "../../nodes/Node.hpp"
#include <vector>
#include <glm/vec2.hpp>


class Snake : public Node {
public:
    Snake();
    ~Snake(); 

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    glm::vec2 m_direction = glm::vec2(1, 0); // Initial direction to the right
    std::vector<glm::vec2> m_bodySegments = { glm::vec2(100, 100) }; // Initial position of the snake's head
    float timer = 0.0f;
    void processInput();
};
