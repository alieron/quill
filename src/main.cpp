cmake_minimum_required(VERSION 3.10)
project(quill-viewer)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SOURCES "src/*.cpp") 
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui)

add_executable(${PROJECT_NAME} ${SOURCES} "${CMAKE_SOURCE_DIR}/lib/*/*/*.cpp" "${CMAKE_SOURCE_DIR}/lib/*/*/*/*.cpp")
LINK_DIRECTORIES(/usr/local/lib)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)