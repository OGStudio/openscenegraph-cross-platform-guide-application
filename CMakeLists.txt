PROJECT(SAMPLE_APPLICATION)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# OpenSceneGraph directories.
SET(OSG_INC_DIR "" CACHE PATH "Path to OpenSceneGraph include directory")
SET(OSG_LIB_DIR "" CACHE PATH "Path to OpenSceneGraph lib directory")
INCLUDE_DIRECTORIES(${OSG_INC_DIR})
LINK_DIRECTORIES(${OSG_LIB_DIR})

# Use C++11.
ADD_DEFINITIONS("-std=c++11")

# Create executable.
ADD_EXECUTABLE(sampleApplication src/main.cpp)
# Link executable with OpenSceneGraph libraries.
TARGET_LINK_LIBRARIES(sampleApplication osg osgDB osgGA osgViewer)
