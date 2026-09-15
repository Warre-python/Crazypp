#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Texture;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void render(const float* vertices, int vertexCount, const unsigned int* indices,
                int indexCount, const glm::mat4& model, const float* color);
    void renderTexture(const float* vertices, int vertexCount, const unsigned int* indices,
                       int indexCount, const glm::mat4& model, const Texture& texture);

private:
    Shader m_shader;
    Shader m_textureShader;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    

};
