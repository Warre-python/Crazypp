#pragma once
#include "Node.hpp"
#include "rendering/Renderer.hpp"

class Sprite : public Node {
public:
    void draw(Renderer& renderer) override;

private:
    float m_vertices[12] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    int m_indices[6] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
};