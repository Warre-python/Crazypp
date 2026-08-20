#include "Input.hpp"
#include <GLFW/glfw3.h>

bool Input::isKeyPressed(int key) {
    GLFWwindow* window = glfwGetCurrentContext();
    return window && glfwGetKey(window, key) == GLFW_PRESS;
}
