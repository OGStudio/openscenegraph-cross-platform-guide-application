CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)
SET(BUILD_SIMULATOR YES CACHE BOOL "Build for simulator. Use false to build for real device")

# Path to external projects:
# * OpenSceneGraph
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../..")

# Specify critical OpenSceneGraph build variables.
SET(OPENGL_PROFILE "GLES2" CACHE STRING "OpenGL variant to use")
SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
SET(BUILD_OSG_APPLICATIONS OFF CACHE BOOL "Do not build OpenSceneGraph samples")
# Configure OpenSceneGraph for simulator or real device.
IF(BUILD_SIMULATOR)
    # Prevent macOS SDK includes that lead to build errors.
    SET(CURL_INCLUDE_DIR "" CACHE STRING "Prevent wrong macOS SDK include" FORCE)
    SET(ZLIB_INCLUDE_DIR "" CACHE STRING "Prevent wrong macOS SDK include" FORCE)
    SET(OSG_BUILD_PLATFORM_IPHONE_SIMULATOR YES CACHE BOOL "Build OSG for simulator")
ELSE()
    SET(OSG_BUILD_PLATFORM_IPHONE YES CACHE BOOL "Build OSG for device")
ENDIF()

# Build and reference OpenSceneGraph.
SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
IF(BUILD_SIMULATOR)
    SET(BUILD_VARIANT "Simulator")
ELSE()
    SET(BUILD_VARIANT "Device")
ENDIF()
SET(OSG_BUILD_DIR "${EXT_PROJ_DIR}/OpenSceneGraph/build/${BUILD_VARIANT}")
# TODO: Uncomment after testing.
#FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
#ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)

# Reference OpenSceneGraph cross-platform guide application.
INCLUDE_DIRECTORIES("${EXT_PROJ_DIR}/openscenegraph-cross-platform-guide-application/src")

# Build osgNativeLib.
ADD_LIBRARY(osgNativeLib STATIC src/osgNativeLib.cpp)
# WARNING: This does not actually link anything. However, this command
# WARNING: makes sure all necessary libraries are built.
TARGET_LINK_LIBRARIES(
    osgNativeLib
    osgViewer
    osgDB
    # osgDB plugins start.
    osgdb_osg
    osgdb_serializers_osg
    # osgDB plugins end.
    osgGA
    osgShadow
    osgText
    osgUtil
    osg
    OpenThreads
)
