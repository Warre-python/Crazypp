#pragma once
#include <glad/glad.h>
#include "Shader.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void render();

private:
    Shader m_shader;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    

};
