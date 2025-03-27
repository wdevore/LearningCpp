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