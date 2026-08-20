#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    void processInput();
    void clear(float r, float g, float b, float a) const;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    
};
