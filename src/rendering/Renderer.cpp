#include "rendering/Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer()
    : m_shader("res/shaders/basic.glsl") {
    m_shader.compile();
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
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}