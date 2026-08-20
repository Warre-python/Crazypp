#pragma once
#include "Shader.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void render();

private:
    Shader m_shader;

};
