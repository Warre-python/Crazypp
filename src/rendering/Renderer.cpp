#include "rendering/Renderer.hpp"
#include "core/Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer()
        : m_shader("res/shaders/basic.glsl"),
            m_textureShader("res/shaders/texture.glsl") {
    m_shader.compile();
        m_textureShader.compile();
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBindVertexArray(0);
}

Renderer::~Renderer() {
    m_shader.detach();
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}   

void Renderer::render(const float* vertices, int vertexCount,
                      const unsigned int* indices, int indexCount,
                      const glm::mat4& model, const float* color) {
    m_shader.use();
    m_shader.uploadVec4f("uColor", glm::vec4(color[0], color[1], color[2], color[3]));
    m_shader.uploadMat4f("model", model);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    m_shader.uploadMat4f(
        "projection",
        glm::ortho(0.0f, static_cast<float>(viewport[2]),
                   static_cast<float>(viewport[3]), 0.0f));
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
    glBindVertexArray(m_vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Renderer::renderTexture(const float* vertices, int vertexCount,
                             const unsigned int* indices, int indexCount,
                             const glm::mat4& model, const Texture& texture) {
    m_textureShader.use();
    m_textureShader.uploadMat4f("model", model);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    m_textureShader.uploadMat4f(
        "projection",
        glm::ortho(0.0f, static_cast<float>(viewport[2]),
                   static_cast<float>(viewport[3]), 0.0f));
    m_textureShader.uploadTexture("ourTexture", 0);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
    glBindVertexArray(m_vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    texture.unbind();
}