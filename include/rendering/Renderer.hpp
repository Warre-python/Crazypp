#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void render(const float* vertices, int vertexCount, const unsigned int* indices,
                int indexCount, const glm::mat4& model, const float* color);

private:
    Shader m_shader;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    

};
