cmake_minimum_required(VERSION 3.10)
project(quill-viewer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SOURCES "src/*.cpp" "${CMAKE_SOURCE_DIR}/lib/*/*/*/*.cpp" "${CMAKE_SOURCE_DIR}/lib/*/*/*/*/*.cpp") 
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui/include)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw3 OpenGL::GL)