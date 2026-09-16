cmake_minimum_required(VERSION 3.15)
project(Crazy++)

# Stel de C++ standaard in
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sla de configuratie van GLFW documentatie en tests over om het bouwen te versnellen
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Voeg GLFW toe aan het CMake project
add_subdirectory(external/glfw)

# Zoek naar de ingebouwde OpenGL bibliotheek van Windows
find_package(OpenGL REQUIRED)

# Zoek naar GLM (OpenGL Mathematics library)
add_subdirectory(external/glm)

include(FetchContent)

FetchContent_Declare(
    freetype
    URL https://github.com/freetype/freetype/archive/refs/tags/VER-2-13-3.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(FT_DISABLE_ZLIB ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BZIP2 ON CACHE BOOL "" FORCE)
set(FT_DISABLE_PNG ON CACHE BOOL "" FORCE)
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
set(FT_DISABLE_BROTLI ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(freetype)




# Definieer je uitvoerbare bestand (executable) inclusief de GLAD broncode
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/glad.c
    src/stb_image.cpp
    src/Input.cpp
    src/Window.cpp
    src/Shader.cpp
    src/Game.cpp


    src/scenes/GameManager.cpp

    src/scenes/ball/Ball.cpp
    src/scenes/ball/BallGame.cpp
    
    src/scenes/snake/Apple.cpp
    src/scenes/snake/Snake.cpp
    src/scenes/snake/SnakeGame.cpp

    src/nodes/Node.cpp
    src/nodes/Transform.cpp
    src/nodes/Sprite.cpp
    src/nodes/Text.cpp
    src/nodes/Texture.cpp
    
    src/rendering/Renderer.cpp
    
    src/physics/CircleCollider.cpp

)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
)

# Geef aan waar de include-mappen staan (voor glad/glad.h en glm)
target_include_directories(${PROJECT_NAME} PRIVATE 
    include
    ${CMAKE_SOURCE_DIR}/external/glm
)

# Koppel GLFW, OpenGL en GLM aan jouw executable
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    OpenGL::GL
    glm::glm
    freetype
)
