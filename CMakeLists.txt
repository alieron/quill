cmake_minimum_required(VERSION 3.10)
project(quill-viewer)
cmake_policy(SET CMP0072 NEW)


# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SOURCE_DIR}/bin)

file(GLOB SOURCES src/main.cpp)
# file(GLOB SOURCES "src/*.cpp" "${SOURCE_DIR}/lib/*/*/*/*.cpp" "${SOURCE_DIR}/lib/*/*/*/*/*.cpp") 
# include_directories(${SOURCE_DIR}/src)
include_directories(lib)
# include_directories(lib/glfw/include)
# include_directories(${SOURCE_DIR}/lib/glm/include)
# include_directories(${SOURCE_DIR}/lib/imgui/include)

add_executable(${PROJECT_NAME} ${SOURCES})
# LINK_DIRECTORIES(/usr/local/lib)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)