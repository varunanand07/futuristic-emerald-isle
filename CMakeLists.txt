cmake_minimum_required(VERSION 3.10)
project(FuturisticEmeraldIsle)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    include
)

file(GLOB SOURCES "src/*.cpp")

add_executable(FuturisticEmeraldIsle ${SOURCES})

target_link_libraries(FuturisticEmeraldIsle
    ${OPENGL_gl_LIBRARY}
    GLEW::GLEW
    glfw
)
