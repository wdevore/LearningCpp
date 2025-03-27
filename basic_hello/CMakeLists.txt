cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)

project(basic_hello VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILES_FOLDER src/)
# set(SOURCE_FILES
#   ${CMAKE_CURRENT_SOURCE_DIR}/src/
#   ${CMAKE_CURRENT_SOURCE_DIR}/include/
# )

# file(GLOB_RECURSE SRC_FILES ${SOURCE_FILES} *.cpp *.h)

# set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/speech.h)
# set(SOURCES src/main.cpp src/speech.cpp include/speech.h)

add_executable(basic_hello
  ${SOURCE_FILES_FOLDER}main.cpp
  ${SOURCE_FILES_FOLDER}speech.cpp
)

target_include_directories(basic_hello PUBLIC include/)