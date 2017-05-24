CMAKE_MINIMUM_REQUIRED(VERSION 3.4.1)
SET(BUILD_SIMULATOR YES CACHE BOOL "Build for simulator. Use false to build for real device")

# Path to external projects:
# * OpenSceneGraph
# -todo-* openscenegraph-cross-platform-guide-application
SET(EXT_PROJ_DIR "${CMAKE_SOURCE_DIR}/../..")

# SDK path mask.
#SET(SDK_PATH_MASK "/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneMASK.platform/Developer/SDKs/iPhoneMASK.sdk")

# Specify critical OpenSceneGraph build variables.
SET(OPENGL_PROFILE "GLES2" CACHE STRING "OpenGL variant to use")
SET(DYNAMIC_OPENTHREADS OFF CACHE BOOL "Link OpenThreads statically")
SET(DYNAMIC_OPENSCENEGRAPH OFF CACHE BOOL "Link OpenSceneGraph statically")
SET(BUILD_OSG_APPLICATIONS OFF CACHE BOOL "Do not build OpenSceneGraph samples")

# Configure OpenSceneGraph for simulator or real device.
IF(BUILD_SIMULATOR)
    # Make sure OpenSceneGraph knows we build for simulator.
    SET(OSG_BUILD_PLATFORM_IPHONE_SIMULATOR YES CACHE BOOL "Build OSG for simulator")
    # Override erroneous OpenSceneGraph iPhone simulator build flags.
    #SET(CMAKE_OSX_ARCHITECTURES "i386;x86_64" CACHE STRING "Simulator architectures" FORCE)
    #TODO:??? SET(CMAKE_CXX_FLAGS "
    # Path to simulator SDK.
    #STRING(REPLACE "MASK" "Simulator" SDK_PATH "${SDK_PATH_MASK}")
    #SET(CMAKE_OSX_SYSROOT "${SDK_PATH}" CACHE STRING "Path to SDK" FORCE)

    # TODO: remove.
    #MESSAGE("SDK path mask: ${SDK_PATH_MASK}")
    #MESSAGE("SDK path: ${SDK_PATH}")
    #MESSAGE("CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES}")
    #MESSAGE("CMAKE_OSX_SYSROOT: ${CMAKE_OSX_SYSROOT}")

ELSE()
    # TODO.
    #STRING(REPLACE "$MASK" "OS" "${SDK_MASK}" SDK_PATH)
    #SET(CMAKE_OSX_SYSROOT "${SDK_PATH}")
    #SET(OSG_BUILD_PLATFORM_IPHONE YES)
ENDIF()

# Build and reference OpenSceneGraph.
SET(OSG_SOURCE_DIR "${EXT_PROJ_DIR}/OpenSceneGraph")
IF(BUILD_SIMULATOR)
    SET(BUILD_VARIANT "Simulator")
ELSE()
    SET(BUILD_VARIANT "Device")
ENDIF()
SET(OSG_BUILD_DIR "${EXT_PROJ_DIR}/OpenSceneGraph/build/${BUILD_VARIANT}")
FILE(MAKE_DIRECTORY ${OSG_BUILD_DIR})
ADD_SUBDIRECTORY(${OSG_SOURCE_DIR} ${OSG_BUILD_DIR})
INCLUDE_DIRECTORIES(${OSG_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OSG_BUILD_DIR}/include)

# Reference OpenSceneGraph cross-platform guide application.
#INCLUDE_DIRECTORIES("${EXT_PROJ_DIR}/openscenegraph-cross-platform-guide-application/src")

# Build osgNativeLib.
ADD_LIBRARY(osgNativeLib STATIC src/osgNativeLib.cpp)
# Libraries must be linked in the specified order.
# Otherwise you may get unsatisified linker errors.
# WARNING: This does not really link, but allows to build only necessary dependencies.
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
# TODO: create single fat library by combining *a libraries.
#INSTALL(
#    TARGETS
#        osgNativeLib
#        osgViewer
#        osgDB
#        # osgDB plugins start.
#        osgdb_osg
#        osgdb_serializers_osg
#        # osgDB plugins end.
#        osgGA
#        osgShadow
#        osgText
#        osgUtil
#        osg
#        OpenThreads
#    RUNTIME DESTINATION "bin/${BUILD_VARIANT}"
#    LIBRARY DESTINATION "lib/${BUILD_VARIANT}"
#    ARCHIVE DESTINATION "lib/${BUILD_VARIANT}"
#)
