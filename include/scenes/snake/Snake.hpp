#pragma once

#include "../../core/Node.hpp"
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
    std::vector<glm::vec2> m_bodySegments; 

    void processInput();
};
