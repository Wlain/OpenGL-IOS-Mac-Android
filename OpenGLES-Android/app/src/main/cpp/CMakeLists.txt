# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.10.2)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
             opengl

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             Opengl.cpp GL/Scene.cpp Common/Utils.cpp)

# build application's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

target_link_libraries( # Specifies the target library.
                        opengl
                        #lib to link
                        android
                        # other libs
                        log
                        EGL
                        GLESv2)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb )
