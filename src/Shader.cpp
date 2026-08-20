#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& filepath) : filepath(filepath), shaderProgramID(0), vertexShader(0), fragmentShader(0) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file for shader: '" << filepath << "'" << std::endl;
        assert(false && "Failed to open shader file");
        return;
    }

    std::stringstream vertexSrc, fragmentSrc;
    std::string line;
    std::stringstream* current = nullptr;

    while (std::getline(file, line)) {
        if (line.find("#type") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                current = &vertexSrc;
            } else if (line.find("fragment") != std::string::npos) {
                current = &fragmentSrc;
            }
        } else if (current != nullptr) {
            *current << line << "\n";
        }
    }

    vertexSource = vertexSrc.str();
    fragmentSource = fragmentSrc.str();
    file.close();
}

Shader::~Shader() {
    // Cleanup is optional; you may want to add glDeleteProgram(shaderProgramID) if needed
}

void Shader::compile() {
    int vertexID, fragmentID;

    // First load and compile the vertex shader
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSrc = vertexSource.c_str();
    glShaderSource(vertexID, 1, &vertexSrc, nullptr);
    glCompileShader(vertexID);

    // Check for errors in compilation
    int success = 0;
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int len = 0;
        glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, ' ');
        glGetShaderInfoLog(vertexID, len, nullptr, &log[0]);
        std::cerr << "ERROR: '" << filepath << "'\n\tVertex shader compilation failed." << std::endl;
        std::cerr << log << std::endl;
        assert(false && "Vertex shader compilation failed");
    }

    // Load and compile the fragment shader
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSrc = fragmentSource.c_str();
    glShaderSource(fragmentID, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentID);

    // Check for errors in compilation
    success = 0;
    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int len = 0;
        glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, ' ');
        glGetShaderInfoLog(fragmentID, len, nullptr, &log[0]);
        std::cerr << "ERROR: '" << filepath << "'\n\tFragment shader compilation failed." << std::endl;
        std::cerr << log << std::endl;
        assert(false && "Fragment shader compilation failed");
    }

    // Link shaders and check for errors
    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexID);
    glAttachShader(shaderProgramID, fragmentID);
    glLinkProgram(shaderProgramID);

    glUseProgram(shaderProgramID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

    // Check for linking errors
    success = 0;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        int len = 0;
        glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, ' ');
        glGetProgramInfoLog(shaderProgramID, len, nullptr, &log[0]);
        std::cerr << "ERROR: '" << filepath << "'\n\tLinking of shaders failed." << std::endl;
        std::cerr << log << std::endl;
        assert(false && "Shader linking failed");
    }
}

void Shader::use() const {
    if (!beingUsed) {
        glUseProgram(shaderProgramID);
        const_cast<Shader*>(this)->beingUsed = true;
    }
}

void Shader::detach() const {
    glUseProgram(0);
    const_cast<Shader*>(this)->beingUsed = false;
}

void Shader::uploadMat4f(const std::string& varName, const glm::mat4& mat4) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::uploadMat3f(const std::string& varName, const glm::mat3& mat3) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniformMatrix3fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat3));
}

void Shader::uploadVec4f(const std::string& varName, const glm::vec4& vec) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform4f(varLocation, vec.x, vec.y, vec.z, vec.w);
}

void Shader::uploadVec3f(const std::string& varName, const glm::vec3& vec) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform3f(varLocation, vec.x, vec.y, vec.z);
}

void Shader::uploadVec2f(const std::string& varName, const glm::vec2& vec) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform2f(varLocation, vec.x, vec.y);
}

void Shader::uploadFloat(const std::string& varName, float val) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform1f(varLocation, val);
}

void Shader::uploadInt(const std::string& varName, int val) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform1i(varLocation, val);
}

void Shader::uploadTexture(const std::string& varName, int slot) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform1i(varLocation, slot);
}

void Shader::uploadIntArray(const std::string& varName, const int* array, int size) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    glUniform1iv(varLocation, size, array);
}

void Shader::uploadBool(const std::string& varName, bool val) {
    int varLocation = glGetUniformLocation(shaderProgramID, varName.c_str());
    use();
    // Convert boolean to 1 (true) or 0 (false) and upload as an integer
    glUniform1i(varLocation, val ? 1 : 0);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) const {
    // This helper function can be used for additional error checking if needed
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, ' ');
        glGetShaderInfoLog(shader, len, nullptr, &log[0]);
        std::cerr << "Shader compilation error (" << type << "):\n" << log << std::endl;
    }
}
