#pragma once
#include <string>
#include "Node.hpp"
#include <array>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include "Shader.hpp"

class Text : public Node {
public:
    Text(const std::string& text = "", const std::string& fontPath = "assets/fonts/arial.ttf", int fontSize = 24);
    ~Text();

    void setText(const std::string& text);
    void setFont(const std::string& fontPath, int fontSize);
    void setColor(float r, float g, float b, float a);

    void update(float deltaTime) override;
    void draw(Renderer& renderer) override;

private:
    struct Glyph {
        GLuint texture = 0;
        glm::ivec2 size = glm::ivec2(0);
        glm::ivec2 bearing = glm::ivec2(0);
        FT_Pos advance = 0;
    };

    bool loadFont();
    void clearGlyphs();

    std::string m_text;
    std::string m_fontPath;
    int m_fontSize;
    std::array<float, 4> m_color;
    FT_Library m_library = nullptr;
    FT_Face m_face = nullptr;
    std::map<unsigned char, Glyph> m_glyphs;
    Shader m_shader;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
};