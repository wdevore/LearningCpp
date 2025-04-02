cmake_minimum_required(VERSION 3.31.0)
project(basic_library VERSION 0.1.0 LANGUAGES C CXX)

# add_library(engine OBJECT engine.cpp)

add_subdirectory(core)

add_executable(basic_library main.cpp)

include(CTest)
enable_testing()

# target_link_libraries(basic_library engine)
target_link_libraries(basic_library core)

target_include_directories(basic_library
 PUBLIC core
)
