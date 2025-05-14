cmake_minimum_required(VERSION 3.10)
project(quill-viewer)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

file(GLOB SOURCES src/*.cpp)
include_directories(src)
include_directories(external)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL glm::glm)
