#include "nodes/Text.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Text::Text(const std::string& text, const std::string& fontPath, int fontSize)
	: m_text(text),
	  m_fontPath(fontPath),
	  m_fontSize(fontSize),
	  m_color{1.0f, 1.0f, 1.0f, 1.0f},
	  m_shader("res/shaders/text.glsl") {
	m_transform.setPosition(0.0f, 0.0f);

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_shader.compile();
	loadFont();
}

Text::~Text() {
	clearGlyphs();
	if (m_face != nullptr) {
		FT_Done_Face(m_face);
	}
	if (m_library != nullptr) {
		FT_Done_FreeType(m_library);
	}
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Text::setText(const std::string& text) {
	m_text = text;
}

void Text::setFont(const std::string& fontPath, int fontSize) {
	m_fontPath = fontPath;
	m_fontSize = fontSize;
	clearGlyphs();
	if (m_face != nullptr) {
		FT_Done_Face(m_face);
		m_face = nullptr;
	}
	loadFont();
}

void Text::setColor(float r, float g, float b, float a) {
	m_color = {r, g, b, a};
}

void Text::update(float deltaTime) {
	(void)deltaTime;
}

void Text::draw(Renderer& renderer) {
	(void)renderer;
	if (m_face == nullptr || m_text.empty()) {
		return;
	}

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	const glm::mat4 projection = glm::ortho(
		0.0f, static_cast<float>(viewport[2]),
		static_cast<float>(viewport[3]), 0.0f);

	m_shader.use();
	m_shader.uploadMat4f("projection", projection);
	m_shader.uploadMat4f("model", getWorldMatrix());
	m_shader.uploadVec4f(
		"textColor",
		glm::vec4(m_color[0], m_color[1], m_color[2], m_color[3]));
	m_shader.uploadInt("text", 0);

	GLboolean blendEnabled = GL_FALSE;
	glGetBooleanv(GL_BLEND, &blendEnabled);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);

	float x = 0.0f;
	float y = 0.0f;
	for (unsigned char character : m_text) {
		auto glyphIt = m_glyphs.find(character);
		if (glyphIt == m_glyphs.end()) {
			continue;
		}

		const Glyph& glyph = glyphIt->second;
		const float xpos = x + static_cast<float>(glyph.bearing.x);
		const float ypos = y - static_cast<float>(glyph.bearing.y);
		const float width = static_cast<float>(glyph.size.x);
		const float height = static_cast<float>(glyph.size.y);

		const float vertices[6][4] = {
			{xpos, ypos, 0.0f, 0.0f},
			{xpos, ypos + height, 0.0f, 1.0f},
			{xpos + width, ypos + height, 1.0f, 1.0f},
			{xpos, ypos, 0.0f, 0.0f},
			{xpos + width, ypos + height, 1.0f, 1.0f},
			{xpos + width, ypos, 1.0f, 0.0f}
		};

		glBindTexture(GL_TEXTURE_2D, glyph.texture);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += static_cast<float>(glyph.advance >> 6);
	}

	if (blendEnabled == GL_FALSE) {
		glDisable(GL_BLEND);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	m_shader.detach();
}

bool Text::loadFont() {
	if (m_fontSize <= 0) {
		return false;
	}

	if (m_library == nullptr && FT_Init_FreeType(&m_library) != 0) {
		std::cerr << "Failed to initialize FreeType\n";
		return false;
	}

	if (FT_New_Face(m_library, m_fontPath.c_str(), 0, &m_face) != 0) {
		std::cerr << "Failed to load font: " << m_fontPath << '\n';
		FT_Done_FreeType(m_library);
		m_library = nullptr;
		return false;
	}

	if (FT_Set_Pixel_Sizes(m_face, 0, static_cast<FT_UInt>(m_fontSize)) != 0) {
		FT_Done_Face(m_face);
		m_face = nullptr;
		return false;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned int character = 0; character < 128; ++character) {
		if (FT_Load_Char(m_face, character, FT_LOAD_RENDER) != 0) {
			continue;
		}

		GLuint texture = 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RED,
			static_cast<GLsizei>(m_face->glyph->bitmap.width),
			static_cast<GLsizei>(m_face->glyph->bitmap.rows),
			0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Glyph glyph;
		glyph.texture = texture;
		glyph.size = glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
		glyph.bearing = glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
		glyph.advance = m_face->glyph->advance.x;
		m_glyphs.emplace(static_cast<unsigned char>(character), glyph);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	return true;
}

void Text::clearGlyphs() {
	for (const auto& [character, glyph] : m_glyphs) {
		(void)character;
		glDeleteTextures(1, &glyph.texture);
	}
	m_glyphs.clear();
}