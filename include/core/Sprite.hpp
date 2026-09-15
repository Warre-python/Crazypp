#pragma once
#include <vector>
#include "Node.hpp"
#include "rendering/Renderer.hpp"

class Texture;

class Sprite : public Node {
public:
    Sprite();
    

    void rectangle(float width, float height);
    void circle(float radius);
    void setColor(float r, float g, float b, float a);
    void setTexture(const Texture* texture);

    
    void draw(Renderer& renderer) override;

private:
    std::vector<float> m_vertices;
    std::vector<float> m_textureVertices;
    std::vector<unsigned int> m_indices;
    const Texture* m_texture = nullptr;
    float m_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
};