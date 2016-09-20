cmake_minimum_required(VERSION 3.6)
project(FFGLPlugin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTARGET_OS_MAC -std=c++11 -stdlib=libc++ -arch i386")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-writable-strings")

find_package(OpenGL REQUIRED)

add_subdirectory(ffgl-host)
include_directories(ffgl-host/lib/ffgl)

set(FFGL_PLUGIN_FILES
        ffgl-host/lib/ffgl/FFGL.cpp
        ffgl-host/lib/ffgl/FFGLPluginInfo.cpp
        ffgl-host/lib/ffgl/FFGLPluginInfoData.cpp
        ffgl-host/lib/ffgl/FFGLPluginManager.cpp
        ffgl-host/lib/ffgl/FFGLPluginSDK.cpp
        ffgl-host/lib/ffgl/FFGLShader.cpp
        ffgl-host/lib/ffgl/FFGLExtensions.cpp
        )

add_library(RGBSource MODULE EmptyEffect.cpp MyPlugin.h ${FFGL_PLUGIN_FILES})
target_link_libraries(RGBSource ${OPENGL_LIBRARIES})
set_target_properties(RGBSource PROPERTIES BUNDLE true)

add_library(EvilShader MODULE EvilShader.cpp ${FFGL_PLUGIN_FILES})
target_link_libraries(EvilShader ${OPENGL_LIBRARIES})
set_target_properties(EvilShader PROPERTIES BUNDLE true)

add_library(UnderwaterLife MODULE UnderwaterLife.cpp ${FFGL_PLUGIN_FILES})
target_link_libraries(UnderwaterLife ${OPENGL_LIBRARIES})
set_target_properties(UnderwaterLife PROPERTIES BUNDLE true)

add_library(Spiral MODULE Spiral.cpp ${FFGL_PLUGIN_FILES})
target_link_libraries(Spiral ${OPENGL_LIBRARIES})
set_target_properties(Spiral PROPERTIES BUNDLE true)

add_library(Plasma MODULE Plasma.cpp ${FFGL_PLUGIN_FILES})
target_link_libraries(Plasma ${OPENGL_LIBRARIES})
set_target_properties(Plasma PROPERTIES BUNDLE true)

add_library(Noise MODULE Noise.cpp ${FFGL_PLUGIN_FILES})
target_link_libraries(Noise ${OPENGL_LIBRARIES})
set_target_properties(Noise PROPERTIES BUNDLE true)

add_library(Springs MODULE Springs.cpp ${FFGL_PLUGIN_FILES})
target_link_libraries(Springs ${OPENGL_LIBRARIES})
set_target_properties(Springs PROPERTIES BUNDLE true)
