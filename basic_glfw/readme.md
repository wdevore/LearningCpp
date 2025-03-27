# Description
A very basic GLFW application using OpenGL

/home/iposthuman/Development/cpp/LearningCpp/basic_glfw/build/_deps/glfw-src

# CMake
This is an example from Gemini for automating the fetching and build of glad source files:
```cmake
# (Omitted: cmake_minimum_required, project, etc.)

add_custom_target(generate_glad
    COMMAND ${CMAKE_COMMAND} -E make_directory glad
    COMMAND ${CMAKE_COMMAND} -E file DOWNLOAD "https://glad.dav1d.de/api/generate?spec=gl&api=gl&profile=core&version=4.6&language=c&generator=c-gl&loader=on" glad.zip
    COMMAND ${CMAKE_COMMAND} -E tar xzf glad.zip -C glad --strip-components 1
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS glad.zip
    VERBATIM
)
add_executable(MyOpenGLProject src/main.cpp glad/src/glad.c)
target_link_libraries(MyOpenGLProject OpenGL GLFW::glfw)
target_include_directories(MyOpenGLProject PUBLIC glad/include)
add_dependencies(MyOpenGLProject generate_glad)

#Fetch GLFW
include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)
```
I didn't use this approach. I went directly to the URL site https://glad.dav1d.de/ and custom configured a *core 4.6* zip file and then unzipped and copied the header and source into a dependencies folder.

This version builds a library and *then* adds it as a link target:
```cmake
include(FetchContent)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36 # Use a specific tag/release
)

FetchContent_MakeAvailable(glad)

# Generate GLAD source and header files
add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/glad/src/glad.c ${CMAKE_BINARY_DIR}/glad/include/glad/glad.h
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/glad/src
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/glad/include/glad
  COMMAND ${CMAKE_COMMAND} -E chdir ${glad_SOURCE_DIR} python ./glad.py --generator c -o ${CMAKE_BINARY_DIR}/glad --api gl=${OPENGL_VERSION} --extensions ${OPENGL_EXTENSIONS}
  DEPENDS glad # Ensure glad is downloaded first
)

add_library(glad_lib 
  ${CMAKE_BINARY_DIR}/glad/src/glad.c
)

target_include_directories(glad_lib
  PUBLIC
    ${CMAKE_BINARY_DIR}/glad/include
)

# Example of linking against glad
add_executable(my_app main.c)
target_link_libraries(my_app glad_lib)
```