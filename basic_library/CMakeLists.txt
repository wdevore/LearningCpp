cmake_minimum_required(VERSION 3.31.0)
project(basic_library VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD           17)
# I want c++17 to the require minimum
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_DIR src)

# Tell cmake to include the "core" folder (aka library). Without it cmake
# will ignore that library whereupon you will get a link failure indicating it
# can't find library "corelib".
add_subdirectory(${SOURCE_DIR}/core)

add_executable(basic_library main.cpp)

include(CTest)
enable_testing()

target_link_libraries(basic_library core)

target_include_directories(basic_library
 PUBLIC core
)
