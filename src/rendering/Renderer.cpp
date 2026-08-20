#include "rendering/Renderer.hpp"

Renderer::Renderer() 
    : m_shader("res/shaders/basic.glsl") {
        

        m_shader.compile();

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


}

Renderer::~Renderer() {
    m_shader.detach();
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}   

void Renderer::render() {
    m_shader.use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, sizeof(m_indices) / sizeof(*m_indices), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}