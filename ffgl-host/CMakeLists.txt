cmake_minimum_required(VERSION 3.6)
project(FFGLHost)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTARGET_OS_MAC -std=c++11 -stdlib=libc++ -arch i386")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-writable-strings")

find_package(OpenGL REQUIRED)
find_package(Glut REQUIRED)

include_directories(lib/ffgl)

set(FFGL_SOURCE_FILES
        lib/ffgl/FFGLExtensions.cpp
        lib/ffgl/FFGLFBO.cpp
        lib/ffgl/FFGLExtensions.cpp
        lib/ffgl/FFGLPluginInstance.cpp
        lib/ffgl/FFGLShader.cpp
        )

set(SOURCE_FILES
        main.cpp
        OSXDebugMessage.cpp
        OSXPluginInstance.cpp
        OSXTimer.cpp
        )
add_executable(FFGLHost ${SOURCE_FILES} ${FFGL_SOURCE_FILES})
target_link_libraries(FFGLHost ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} "-framework CoreFoundation")
