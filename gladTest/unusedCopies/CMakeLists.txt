cmake_minimum_required(VERSION 3.12)
project(OpenGLCube)

set(CMAKE_CXX_STANDARD 11)

# Add the necessary packages
find_package(OpenGL REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} include)

# GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# STB_IMAGE
include_directories(${CMAKE_SOURCE_DIR}/include)

# GLAD
add_library(GLAD "include/glad/glad.c")
include_directories(${CMAKE_SOURCE_DIR}/include/glad)

# Source files
set(SOURCES
    src/main.cpp
    include/stb_image.h
    #include/glm//glm/glm.hpp
    #include/glm/glm/gtc/matrix_transform.hpp
    src/Shader.cpp
    src/Shader.hpp
    src/Camera.cpp
    src/Camera.hpp
    shaders/vertex.glsl
    shaders/fragment.glsl
)

# GLM
#set(GLM_INCLUDE_DIRS "include")
add_subdirectory(include/glm EXCLUDE_FROM_ALL)

add_executable(OpenGLCube ${SOURCES})

# Link libraries
target_link_libraries(OpenGLCube ${OPENGL_LIBRARIES} glfw GLAD ${CMAKE_DL_LIBS} glm)

# Copy shader files to build directory
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY textures DESTINATION ${CMAKE_BINARY_DIR})