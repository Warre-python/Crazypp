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

# Definieer je uitvoerbare bestand (executable) inclusief de GLAD broncode
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/glad.c
    src/Window.cpp
    src/Shader.cpp
    src/Game.cpp
    src/objects/Player.cpp
    src/core/Node.cpp
    src/core/Transform.cpp
    src/rendering/Renderer.cpp
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
)
