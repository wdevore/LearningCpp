cmake_minimum_required(VERSION 3.31.0)
project(basic_triangle VERSION 0.1.0 LANGUAGES C CXX)

# I want to target only c++17
set(CMAKE_CXX_STANDARD 17)

# Add Fetch feature
include(FetchContent)

# ----------------- GLFW -------------------
# GLFW setup using FetchContent
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4 # Or the latest stable tag
)
FetchContent_MakeAvailable(glfw)

# GLAD files
set(GLAD_SOURCES dependencies/glad/src)
set(GLAD_INCLUDES dependencies/glad/include)

set(CODE_SOURCES src)

add_executable(basic_triangle
  ${CODE_SOURCES}/main.cpp
  ${GLAD_SOURCES}/glad.c
)

target_link_libraries(basic_triangle 
  PRIVATE glfw
  PRIVATE OpenGL
)

# message("glad dir: ${glad_SOURCE_DIR}")
target_include_directories(basic_triangle
  PRIVATE ${GLAD_INCLUDES}
  PRIVATE ${glfw_SOURCE_DIR}/deps
  PRIVATE ${glfw_SOURCE_DIR}/include
)
