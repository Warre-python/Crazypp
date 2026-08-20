#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
    public:
        Shader(const std::string& filepath);
        ~Shader();

        int shaderProgramID;

        void compile();
        void use() const;
        void detach() const;

        // Matrix uploads
        void uploadMat4f(const std::string& varName, const glm::mat4& mat4);
        void uploadMat3f(const std::string& varName, const glm::mat3& mat3);

        // Vector uploads
        void uploadVec4f(const std::string& varName, const glm::vec4& vec);
        void uploadVec3f(const std::string& varName, const glm::vec3& vec);
        void uploadVec2f(const std::string& varName, const glm::vec2& vec);

        // Scalar uploads
        void uploadFloat(const std::string& varName, float val);
        void uploadInt(const std::string& varName, int val);

        // Texture and array uploads
        void uploadTexture(const std::string& varName, int slot);
        void uploadIntArray(const std::string& varName, const int* array, int size);
        void uploadBool(const std::string& varName, bool val);

    private:
        bool beingUsed = false;
        std::string vertexSource;
        std::string fragmentSource;
        std::string filepath;
        int vertexShader;
        int fragmentShader;

        void checkCompileErrors(unsigned int shader, const std::string& type) const;
};