#pragma once
#include "Node.hpp"

class Texture : public Node {
public:
    Texture(const std::string& path);
    ~Texture();
    void bind() const;
    void unbind() const;
    unsigned int getID() const { return m_textureID; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
private:
    unsigned int m_textureID;
    int m_width;
    int m_height;
};