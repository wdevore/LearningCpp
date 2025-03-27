cmake_minimum_required(VERSION 3.10.0)
project(basic_glfw VERSION 0.1.0 LANGUAGES C CXX)

# I want target only c++17
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
# message("glfw dir: " ${glfw_SOURCE_DIR})

# --------- Glad --------------------------
# We don't need to do this because I manually generated and downloaded the
# glad wrappers via: https://glad.dav1d.de/
# The settings are listed in glad.h

# This fetch only retrieves the generator code. You still need to use Cmake's
# COMMAND features to talk to the generator URL with custom
# parms and then request to download the zip. SEE README in this project.
# FetchContent_Declare(
#   glad
#   GIT_REPOSITORY https://github.com/Dav1dde/glad.git
#   GIT_TAG        v2.0.8 #Or latest release
# )
# FetchContent_MakeAvailable(glad)

# GLAD files
set(GLAD_SOURCES dependencies/glad/src)
set(GLAD_INCLUDES dependencies/glad/include)

add_executable(basic_glfw
  main.cpp
  ${GLAD_SOURCES}/glad.c
)

target_link_libraries(basic_glfw 
  glfw
  OpenGL
)

# message("glad dir: " ${glad_SOURCE_DIR})
target_include_directories(basic_glfw
  PUBLIC ${GLAD_INCLUDES}
  PUBLIC ${glfw_SOURCE_DIR}/deps
  PUBLIC ${glfw_SOURCE_DIR}/include
)
