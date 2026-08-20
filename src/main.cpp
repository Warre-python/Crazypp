#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.hpp"

int main() {
    
    Game game;
    game.run();

    

    glfwTerminate();
    return 0;
}
